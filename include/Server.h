#pragma once

#define  define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "GoodsControler.h"
#include "Good.h"
#include "UsersControler.h"
#include "log.h"
#include "Command.h"
#include "textProtocol.h"
#include<thread>
#include "OrdersControler.h"

#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")

#define ConsumersControlerPath ("../res/Consumer") 
#define GoodsControlerPath ("../res/Good") 
#define SellersControlerPath ("../res/Seller")
#define LogPath ("../res/server.log")
#define OdersPath ("../res/Order")

typedef  unsigned int CMD;
typedef int ClientType;

class Server
{
private:
	mutex usingLocker;
	thread* autoSave;
	static Server* instance;
	Server();
	void autoSavingThread();
	void save();
public:
	static void serverMain();
	OrdersControler* allOrders;
	ConsumersControler* consumers;
	SellersControler* sellers;
	GoodsControler* goods;
	int Main1();
	static Server* getInstance();
	~Server();
	//Dialog* dialog;//just for test
};

class Dialog {
private:
	std::condition_variable Run;
	std::mutex lock;
	std::thread* waitThread;
	std::thread* dialogThread;
	enum Command status;
	int step;
	CMD cmd;
	idType userID;
	idType tempID;
	ClientType userType;
	Server* server;
	User* user;
	Text* input;
	Text* output;
	Order* orderNow;
	SOCKET serverSocket;
	SOCKET clientSocket;

	void Dialogmanage();
	void manageSignIn();
	void manageLogIn();
	void manageLogOut();
	void manageIncome();
	void manageGoodsPulling();
	void manageAddGood();
	void manageChange();
	void manageTargetPull();
	void manageOrder();
	void manageSoldPull();
	void manageDiscount();
public:
	~Dialog();
	Dialog(Server* server, Text& in, Text& out);
	Dialog(Server*s,SOCKET Client, SOCKET Cerver);
	void run();
};

