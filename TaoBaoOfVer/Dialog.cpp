#include "Server.h"

#define sendV(tag,x){output->setString(tag, to_string(x)); }
#define sendT(tag,x){output->setString(tag,x);}
#define recvV(tag) (input->getValue(tag))
#define recvT(tag) (input->getString(tag))
#define CUser ((Consumer*)User)
#define SUser ((Seller*)User)
#define sellers (server->sellers)
#define consumers (server->consumers)
#define goods (server->goods)



Dialog::~Dialog()
{
    if (waitThread != NULL)delete waitThread;
    delete dialogThread;
    delete output;
    delete input;
}

Dialog::Dialog(Server* _server, Text& in, Text& out) {
    userType = Visitor;
    status = Exit;
    step = 1;
	server = _server;
    input=&in;
    output = &out;
    waitThread = NULL;
    dialogThread= new thread(&Dialog:: Dialogmanage,this);
}

void Dialog::run()
{
    std::chrono::milliseconds dura(4000);
    std::this_thread::sleep_for(dura);
    Run.notify_one();
}

void Dialog::Dialogmanage()
{
    while (1) {
        bool notSend=false;
        while (!input->infoReady() || !output->empty()) {
            std::unique_lock <std::mutex> lck(lock); waitThread=new thread(&Dialog::run, this);  Run.wait(lck);
        }
       cmd=recvV("cmd"); cout << "sever recv :" << input->buffer() << endl;
        sendV("cmd",cmd);

     //   usingLocker.lock();
        switch (cmd)
        {
        case Exit: step = 1; if (userType == HalfSeller || userType == HalfConsumer)userType = Visitor; break;
            break;
        case ShowGoods:/**/cmd = status; break;
        case LogIn: manageLogIn();
            break;
        case LogOut:
            break;
        case SignIn:manageSignIn();
            break;
        case End:
           // server->save(); 
            return;
            break;
        default:
            break;
        }
        if(status==Exit){ step = 1; if (userType == HalfSeller || userType == HalfConsumer)userType = Visitor; }//outway:status=Exit
        //usingLocker.unlock();
        if (!notSend) {
            output->sendInfo();
            input->clear();
        }
        status = (Command)cmd;
    }
}

void Dialog::manageSignIn()
{
    switch (step) {
    case 1:
        userType=recvV("Type");
        if (userType == HalfConsumer)  userID = consumers->suggestID();
        else if (userType == HalfSeller) userID = sellers->suggestID();
        sendV("ID",userID);
        if (userID != _INVALID_ID)step++;
    case 2:
        string passWd;
        passWd=recvT("passWd");
        string name;
        name=recvT("name");
        if (userType == HalfConsumer) {
            user = new Consumer();
            consumers->addToMemory(user);
            userType = ConsumerUser;
        }
        else if (userType == HalfSeller) {
            user = new Seller();
            sellers->addToMemory(user);
            userType = SellerUser;
        }
        user->changePassWord(passWd);
        user->changeName(name);
        status = Exit;
        step = 1;
    }
}

void Dialog::manageLogIn()
{
    bool flag = false;
    switch (step)
    {
    case 1:
        userType=recvV("Type");
        userID=recvV("ID");
        flag = false;
        if (userType == ConsumerUser) {
            flag = consumers->containsInFile(userID);
            if (flag)userType=HalfConsumer;
        }
        else if (userType == SellerUser) {
            flag = sellers->containsInFile(userID);
            if (flag)userType = HalfSeller;
        }
        if (flag)step++;
        else { step = 0; userType = Visitor; }
        sendV("Flag",flag);
        break;        
    default:
        string passWord;
        passWord=recvT("passWd");
        flag = user->matchWithPassWord(passWord);  
        sendV("Flag",flag);
        if (!flag)sendV("Step",5-step);
        if (flag) {
            step = 0;
            if (userType == HalfConsumer)userType = ConsumerUser;
            else if (userType == HalfSeller)userType = SellerUser;
            sendT("Name",user->Name());
            sendV("Money",user->Money());
        }
        else { step++; if (step > 4)status = Exit; }
        break;
    }
}

