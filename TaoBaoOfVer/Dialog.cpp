#include "Server.h"

#define sendV(tag,x){output->setString(tag, to_string(x)); }
#define sendT(tag,x){output->setString(tag,x);}
#define recvV(tag) (input->getValue(tag))
#define recvT(tag) (input->getString(tag))
#define ExitProcess {status=Exit;}
#define HasLogIn (userType==ConsumerUser||userType==SellerUser)

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
    std::chrono::milliseconds dura(500);
    std::this_thread::sleep_for(dura);
    Run.notify_one();
}

void Dialog::Dialogmanage()
{
    while (1) {
        while (!input->infoReady() || !output->empty()) {
            std::unique_lock <std::mutex> lck(lock); waitThread=new thread(&Dialog::run, this);  Run.wait(lck);
        }
       cmd=recvV("cmd"); 
       cout << "sever recv :" << input->buffer() << endl;
        if (status == Exit) { status = (Command)cmd; step = 1; }
     //   usingLocker.lock();
        switch (cmd)
        {
        case Exit: step = 1; if (userType == HalfSeller || userType == HalfConsumer)userType = Visitor; break;
            break;
        case ShowGoods:/**/cmd = status; break;
        case LogIn: manageLogIn();
            break;
        case LogOut:manageLogOut();
            break;
        case SignIn:manageSignIn();
            break;
        case Income:manageIncome();
            break;
        case AskGoodsInfo:manageGoodsPulling();
        case End:
           // server->save(); 
            return;
            break;
        default:
            break;
        }
        if(status==Exit){ step = 1; if (userType == HalfSeller || userType == HalfConsumer)userType = Visitor; }//outway:status=Exit
        //usingLocker.unlock();
        if (!output->empty()) {
            sendV("cmd", cmd);
            output->sendInfo();
        }
        input->clear();
    }
}

void Dialog::manageSignIn()
{
    string passWd;
    string name;
    bool flag=false;
    switch (step) {
    case 1:
        userType = recvV("Type");
        if (userType == ConsumerUser) { userID = consumers->suggestID(); userType = HalfConsumer; }
        else if (userType == SellerUser) {   userID = sellers->suggestID(); userType = HalfSeller;}
        sendV("ID",userID);
        if (userID != _INVALID_ID)step++;
        break;
    case 2:
        passWd=recvT("passWd");
        name=recvT("Name");
        if (userType == HalfConsumer) {
            user = new Consumer(userID,name,passWd);
            consumers->addToMemory(user);
            consumers->saveFile(userID);
        }
        else if (userType == HalfSeller) {
            user = new Seller(userID,name,passWd);
            sellers->addToMemory(user);
            sellers->saveFile(userID);
        }
        step++;
        break;
    case 3:
        flag=recvV("Flag");
        if (flag) {
            if (userType == HalfConsumer) {
                userType = ConsumerUser;
            }
            else if (userType == HalfSeller) {
                userType = SellerUser;
            }
        }
        else { 
            if (userType == HalfConsumer) {
                consumers->releaseFromMemoryIntoFile(userID);
            }
            else if (userType == HalfSeller) {
                sellers->releaseFromMemoryIntoFile(userID);
            }
        }
        ExitProcess;
        break;
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
        else { step = 1; userType = Visitor; }
        sendV("Flag",flag);
        break;        
    default:
        string passWord;
        passWord=recvT("passWd");
        user =(User*)( (userType == HalfConsumer  )?consumers->readFromFile(userID): sellers->readFromFile(userID));
        flag = user->matchWithPassWord(passWord);  
        sendV("Flag",flag);
        if (flag) {
            if (userType == HalfConsumer)userType = ConsumerUser;
            else if (userType == HalfSeller)userType = SellerUser;
            sendT("Name",user->Name());
            sendV("Money",user->Money());
            ExitProcess;
        }
        else { 
            sendV("Step", 5 - step); 
            step++; 
            if (step > 5) {
                ExitProcess;
            }
        }
        break;
    }
}

void Dialog::manageLogOut()
{
    switch (step)
    {
    case 1:
        if (!HasLogIn) {
            ExitProcess;
        }else
        switch (userType)
        {
        case ConsumerUser:
            consumers->releaseFromMemoryIntoFile(user->id());            
            break;
        case SellerUser:
            sellers->releaseFromMemoryIntoFile(user->id());
        default:
            break;
        }
        userType = Visitor;
        ExitProcess;
        break;
    default:
        break;
    }
}

void Dialog::manageIncome()
{
    bool flag;
    moneyType money;
    switch(step) {
    case 1:
        if (!HasLogIn) {
            ExitProcess; break;
        }
        money = recvV("Money");
        flag=user->income(money);
        if (flag&&userType == ConsumerUser) {
            consumers->saveFile(user->id());
        }
        else if (flag&&userType == SellerUser) {
            sellers->saveFile(user->id());
        }
        else flag = false;
        sendV("Flag", flag);
        break;
    default:
        break;
    }
}

void Dialog::manageGoodsPulling()
{
    bool flag=false;
    idType goodID=_INVALID_ID;
    int num = 7;
    switch (step) {
    case 1:
        goodID = goods->maxID();
        step++;
        //NO break here !
    case 2:
        if (goodID == _INVALID_ID) {
            goodID = recvV("ID");
        }
        while (num>=0&&goodID > _INVALID_ID) {
            if (goods->containsInMemory(goodID)) {
                if (num == 0)break;
                sendT("Good",goods->getObjectInMemory(goodID)->turnIntoString());
                    num--;
            }
            goodID--;
        }
        if (num == 7) {
            flag = false;
        }
        else flag = true;
            sendV("Flag", flag);
            sendV("ID", goodID);
            if (goodID == _INVALID_ID)ExitProcess;
        break;
    default:

            break;
    }
}

