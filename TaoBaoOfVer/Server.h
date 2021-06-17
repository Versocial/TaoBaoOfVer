#pragma once
#include "GoodsControler.h"
#include "UsersControler.h"
#include "log.h"
#include "Command.h"
#include "textProtocol.h"
#include<thread>

#define ConsumersControlerPath ("../res/Consumer") 
#define GoodsControlerPath ("../res/Good") 
#define SellersControlerPath ("../res/Seller")
#define LogPath ("../res/server.log")

typedef  unsigned int CMD;
typedef int ClientType;

class Server
{
private:
	mutex usingLocker;
	thread* autoSave;
	static Server* instance;
	Server(Text& in, Text& out);
	void serverMain();
	void autoSavingThread();
	void save();
public:
	ConsumersControler* consumers;
	SellersControler* sellers;
	GoodsControler* goods;
	int Main1();
	static Server* getInstance(Text& in, Text& out);
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
	ClientType userType;
	Server* server;
	User* user;
	Text* input;
	Text* output;

	void Dialogmanage();
	void manageSignIn();
	void manageLogIn();
	void manageLogOut();
	void manageIncome();
	void manageGoodsPulling();
public:
	~Dialog();
	Dialog(Server* server, Text& in, Text& out);
	void run();
};

