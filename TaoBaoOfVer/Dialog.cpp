#include "Server.h"

#define send(x) {;*output<<" "<<(x)<<" ";}
#define recv(x) {;*input>>(x);}
#define CUser ((Consumer*)User)
#define SUser ((Seller*)User)
#define sellers (server->sellers)
#define consumers (server->consumers)
#define goods (server->goods)



Dialog::Dialog(Server*_server, istream* in, ostream* out) {
    userType = Visitor;
    status = Exit;
    step = 1;
	server = _server;
    input = in;
    output = out;
    new thread(&Dialog:: Dialogmanage,this);
}

void Dialog::run()
{
    cout << "\nco";
    std::chrono::milliseconds dura(4000);
    std::this_thread::sleep_for(dura);
    cout << "ol\n";
    Run.notify_one();
}

void Dialog::Dialogmanage()
{
    while (1) {
        std::unique_lock <std::mutex> lck(lock); 
        while (EOF==input->peek()) { new thread(&Dialog::run,this);  Run.wait(lck); }
            recv(cmd); cout << "ser:" << cmd << endl;
     //   usingLocker.lock();
        switch (cmd)
        {
        case Exit: step = 1; if (userType == HalfSeller || userType == HalfConsumer)userType = Visitor; break;
            break;
        case ShowGoods:/**/cmd = status; break;
        case LogIn:            
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
        status = (Command)cmd;
    }
}

void Dialog::manageSignIn()
{
    switch (step) {
    case 1:
        send(cmd);
        recv(userType);
        if (userType == HalfConsumer)  userID = consumers->suggestID();
        else if (userType == HalfSeller) userID = sellers->suggestID();
        send(userID);
        if (userID != _INVALID_ID)step++;
    case 2:
        send(cmd);
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
        send(cmd);
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
        send(cmd);
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

