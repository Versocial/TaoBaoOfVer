#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Server.h"
//#define AvoidConfictFromSaving  ; lock_guard<mutex> temp_lock_guard(usingLocker);

#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")

Server* Server::instance = NULL;

Server::Server() {
    consumers = ConsumersControler::getInstance(ConsumersControlerPath);
    sellers = SellersControler::getInstance(SellersControlerPath);
    goods = GoodsControler::getInstance(GoodsControlerPath);
    //autoSave = new thread(&Server::autoSavingThread, this);
    Logger::setLogPath(LogPath);
  //  Dialog* dialog= new Dialog(this, in, out);


}


void Server::serverMain()
{
    Server* server = Server::getInstance();
    while (1) {
        SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        sockaddr_in sockAddr;
        memset(&sockAddr, 0, sizeof(sockAddr)); 
        sockAddr.sin_family = PF_INET;  
        sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        sockAddr.sin_port = htons(1234);  
        bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        listen(servSock, 20);

        while (1) {
            SOCKADDR clntAddr;
            int nSize = sizeof(SOCKADDR);
            SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
            new Dialog(server,clntSock, servSock);
        }
    }

    delete(server);
    WSACleanup();
    return ;

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


Server* Server::getInstance()
{
    if (instance == NULL) { 
        instance = new Server(); 
        instance->allOrders = OrdersControler::getInstance(OdersPath);
        instance->allOrders->readOutAllFromFile();
    }
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
