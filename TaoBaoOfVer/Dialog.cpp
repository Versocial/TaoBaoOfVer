#include "Server.h"

#define send(x) {output->clear();*output<<" "<<(x);}
#define recv(x) {*input>>(x);}
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

Dialog::Dialog(Server* _server, char* in, char* out) {
    userType = Visitor;
    status = Exit;
    step = 1;
	server = _server;
    inBuffer = in;
    outBuffer = out;
    waitThread = NULL;
    dialogThread= new thread(&Dialog:: Dialogmanage,this);
    output = new ostringstream("");
    input = new istringstream("");
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
        while (!*inBuffer||*outBuffer) {
            std::unique_lock <std::mutex> lck(lock); waitThread=new thread(&Dialog::run, this);  Run.wait(lck);
        }
        output->clear();
        output->str("");
        input->str(inBuffer); 
        recv(cmd); cout << "ser:" << cmd << endl;
        send(cmd);
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
        //usingLocker.unlock();
        memcpy(outBuffer, output->str().c_str(), strlen(output->str().c_str()));
        *inBuffer = 0;
        status = (Command)cmd;
    }
}

void Dialog::manageSignIn()
{
    switch (step) {
    case 1:
        recv(userType);
        if (userType == HalfConsumer)  userID = consumers->suggestID();
        else if (userType == HalfSeller) userID = sellers->suggestID();
        send(userID);
        if (userID != _INVALID_ID)step++;
    case 2:
        string passWd;
        recv(passWd);
        string name;
        recv(name);
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
        recv(userType);
        recv(userID);
        flag = false;
        if (userType == ConsumerUser) {
            flag = consumers->containsInFile(userID);
            if (flag)userType==HalfConsumer;
        }
        else if (userType == SellerUser) {
            flag = sellers->containsInFile(userID);
            if (flag)userType = HalfSeller;
        }
        if (flag)step++;
        else { step = 0; userType = Visitor; }
        send(flag);
        break;        
    default:
        string passWord;
        recv(passWord);
        flag = user->matchWithPassWord(passWord);     
        if (step > 4)flag = false;
        send(flag);
        if (!flag)send(5-step);
        if (flag) {
            step = 0;
            if (userType == HalfConsumer)userType = ConsumerUser;
            else if (userType == HalfSeller)userType = SellerUser;
        }
        else step++;
        break;
    }
}

