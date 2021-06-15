#include "Server.h"
//#define AvoidConfictFromSaving  ; lock_guard<mutex> temp_lock_guard(usingLocker);
typedef  unsigned char CMD;
typedef bool ClientType;
enum   _CMD {
    LoginIDCheck,
    LoginPassWordCheck,
    LogOut
};
enum _ClientType {
    ConsumerUser,
    SellerUser 
};

Server* Server::instance = NULL;

Server::Server(istream& in,ostream& out) {
    this->input = &in; this->output = &out;
    consumers = ConsumersControler::getInstance(ConsumersControlerPath);
    sellers = SellersControler::getInstance(SellersControlerPath);
    goods = GoodsControler::getInstance(GoodsControlerPath);
    autoSave = new thread(&Server::autoSavingThread, this);
    Logger::setLogPath(LogPath);
}

void Server::serverMain()
{
    CMD cmd;
    idType tempID;
    while (1) {
        *input >> cmd;
        usingLocker.lock();
        switch (cmd)
        {           
        case LoginIDCheck:*input >> tempID; *output; break;
        case LoginPassWordCheck:
        case LogOut:;
        default:
            break;
            
        }
        usingLocker.unlock();
    }
}

void Server::autoSavingThread()
{
    while (1) {
        Logger::log_2("waiting for save.");
        this_thread::sleep_for(chrono::minutes(1));
        Logger::log_2("begin to save.");
        save();
        Logger::log_1("saved");
    }
}

void Server::save()
{
    lock_guard<mutex> temp_lock_guard(usingLocker);
    consumers->save();
    sellers->save();
    goods->save();
}


Server* Server::getInstance(istream&in,ostream &out)
{
    if (instance == NULL) { instance = new Server(in, out); }
    return instance;
}

Server::~Server()
{
    lock_guard<mutex> temp_lock_guard(usingLocker);
    delete consumers;
    delete sellers;
    delete goods;
    delete autoSave;
}
