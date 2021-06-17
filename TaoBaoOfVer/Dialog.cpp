#include "Server.h"
#define sendV(tag,x){output->setString(tag, to_string(x)); }
#define sendT(tag,x){output->setString(tag,x);}
#define recvV(tag) (input->getValue(tag))
#define recvT(tag,x) (input->getString(tag,x))
#define ExitProcess {status=Exit;}
#define HasLogIn (userType==ConsumerUser||userType==SellerUser)

#define CUser ((Consumer*)User)
#define SUser ((Seller*)User)
#define sellers (server->sellers)
#define consumers (server->consumers)
#define orders (server->allOrders)
#define goods (server->goods)
#define MAXPULLNUM 7


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

Dialog::Dialog(Server* s, SOCKET clientS, SOCKET serverS)
{

    char inBuffer [300];
    char outBuffer [300];
    Text in(inBuffer, 300);
    Text out (outBuffer, 300);
    userType = Visitor;
    status = Exit;
    step = 1;
    server = s;
    serverSocket = serverS;
    clientSocket = clientS;
    input = &in;
    output = &out;
    waitThread = NULL;
    dialogThread = new thread(&Dialog::Dialogmanage, this);
    dialogThread->join();

}

void Dialog::run()
{
    while (1) {
        //Run.notify_one();
        
    }
}

void Dialog::Dialogmanage()
{
    while (1) {
        int len = recv(clientSocket, input->buffer(), 300, 0);
        input->buffer()[len] = 0;
        output->clear();
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
            break;
        case AddGood:manageAddGood();
            break;
        case ChangeInfo:manageChange();
            break;
        case Target:manageTargetPull();
            break;
        case ManageOrder:manageOrder();
            break;
        case PullSoldOrder:manageSoldPull();
            break;
            break;
        case End:
           // server->save();
            delete this;
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
            send(clientSocket, output->buffer(), strlen(output->buffer()),0);
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
        recvT("passWd",passWd);
        recvT("Name", name);
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
        recvV("Flag",flag);
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
        recvT("passWd",passWord);
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
    int num = MAXPULLNUM;
    switch (step) {
    case 1:
        goodID = goods->maxID();
        step++;
        //NO break here !
    case 2:
        if (goodID == _INVALID_ID) {
            goodID = recvV("ID");
        }
        while (num>=0&&goodID > goods->startID()) {
            if (goods->containsInMemory(goodID)) {
                if (num == 0)break;
                sendT(("Good"+to_string(MAXPULLNUM-num)),goods->getObjectInMemory(goodID)->turnIntoString());
                    num--;
            }
            goodID--;
        }
        sendV("Num", MAXPULLNUM - num);
        if (num == MAXPULLNUM) {
            flag = false;
        }
        else flag = true;
            sendV("Flag", flag);
            if (goodID == goods->startID()) { 
                sendV("ID", _INVALID_ID); ExitProcess;
            }
            else sendV("ID", goodID);
        break;
    default:

            break;
    }
}

void Dialog::manageAddGood()
{
    string name;
    moneyType price;
    Number selling;
    GoodType type;
    Good* good;
    switch (step) {
    case 1:
        if (userType != SellerUser) {
            sendV("ID", _INVALID_ID);
            ExitProcess; break;
        }
        tempID = goods->suggestID();
        sendV("ID",tempID);
        if (tempID == _INVALID_ID) {
            ExitProcess; break;
        }
        step++;
        break;
    case 2:
        recvT("Name",name);
        type = (GoodType)recvV("Type");
        selling = recvV("Sell");
        price = recvV("Price");
        good = Good::newGood(type, tempID, user->id(), name, price, selling);
        goods->addToMemory(good);
        goods->saveFile(tempID);
        ((Seller*)user)->addGood(tempID);
        sellers->saveFile(user->id());
        ExitProcess;
        break;
    default:
        break;
    }
}

void Dialog::manageChange()
{
    bool flag;
    string info;
    string pass;
    switch (step)
    {
    case 1:
        if (!HasLogIn) { ExitProcess; break; }
        flag=recvV("Flag");
        if (flag) {//change password
             recvT("PassWd",pass);
            flag = user->matchWithPassWord(pass);
            sendV("Flag", flag);
            ExitProcess;
        }
        else {//change name
             recvT("Text",info);
            user->changeName(info);
            if (userType == ConsumerUser)consumers->saveFile(user->id());
            else sellers->saveFile(user->id());
            step++;
        }
        break;
    case 2:
        flag = recvV("Flag");
         recvT("PassWd",pass);
        if (flag) {
            user->changePassWord(pass);
            if (userType == ConsumerUser)consumers->saveFile(user->id());
            else sellers->saveFile(user->id());
        }
        ExitProcess;
    default:
        break;
    }
}

void Dialog::manageTargetPull()
{
    idType id;
    int num = 0;
    switch (step)
    {
    case 1:
        num = recvV("Num");
        sendV("Num",num);
        for (int i = 0; i < num; i++) {
            id = recvV(to_string(i));
            string toSend = "0";
            if (goods->containsInMemory(id))toSend = ((Good*)goods->getObjectInMemory(id))->turnIntoString();
            sendT(to_string(id), toSend);
        }
        ExitProcess;
    default:
        break;
    }
}

void Dialog::manageOrder()
{
    idType id;
    string info;
    int flag;
    istringstream inputs;
    switch (step)
    {
    case 1:
        if (userType != ConsumerUser) {
            ExitProcess;
            break;
        }
        id = orders->suggestID();
         recvT("OD",info);
        inputs.str(info);
        orderNow = (Order*)orders->theOrder()->getByStream(inputs);
        orders->addToMemory(orderNow);
        flag=orderNow->startOrder(goods);
        if (!flag) {
            flag = 2;
            ExitProcess;
        }
        else if (orderNow->totalPrice() > user->Money()) {
            flag = 1;
            ExitProcess;
        }
        else flag = 0;
        sendV("Flag", flag);
        sendV("Price", orderNow->totalPrice());
        step++;
        break;
    case 2:
        flag = recvV("Flag");
        if (flag == true) {
            if (!sellers->containsInMemory(orderNow->SellerID())) {
                if (sellers->containsInFile(orderNow->SellerID())) { sellers->readFromFile(orderNow->SellerID()); }
            }
            if (sellers->containsInMemory(orderNow->SellerID())) {
                orderNow->finishOrder(goods);
                orders->saveFile(orderNow->id());
                user->outcome(orderNow->totalPrice());
                ((Seller*)sellers->getObjectInMemory(orderNow->SellerID()))->income(orderNow->totalPrice());
                ((Seller*)sellers->getObjectInMemory(orderNow->SellerID()))->addOrderID(orderNow->id());
                consumers->saveFile(user->id());
                sellers->saveFile(orderNow->SellerID());
                sendV("Flag", true);
            }
            else sendV("Flag", false);
        }
        else {
            orderNow->concelOrder(goods);
        }
        ExitProcess;
        break;
    default:ExitProcess;
        break;
    }
}
void Dialog::manageSoldPull()
{
    int num = 0;
    switch (step)
    {
    case 1:
        for (idType id : ((Seller*)user)->soldOders) {
            if (orders->containsInMemory(id)) {
                string tempi = ((Order*)(orders->getObjectInMemory(id)))->turnIntoString();
                sendT(to_string(num), tempi);
                    num++;
            }
        }
        sendV("Num", num);
        ExitProcess;
        break;
    default:
        ExitProcess;
        break;
    }
}
/*
@L
c
10001
eveveve
@P
@car
@shop
10001

*/
