#pragma once
#include "GoodsControler.h"
#include "UsersControler.h"
#include "log.h"
#include "Command.h"
#include<thread>
//using namespace ::std;

#define ConsumersControlerPath ("../res/Consumer") 
#define GoodsControlerPath ("../res/Good") 
#define SellersControlerPath ("../res/Seller")
#define LogPath ("../res/server.log")

typedef  unsigned int CMD;
typedef bool ClientType;

class Server
{
private:
	mutex usingLocker;
	thread* autoSave;
	static Server* instance;
	Server(char* in, char* out);
	void serverMain();
	void autoSavingThread();
	void save();
public:
	ConsumersControler* consumers;
	SellersControler* sellers;
	GoodsControler* goods;
	int Main1();
	static Server* getInstance(char*in, char* out);
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
	istringstream* input;
	ostringstream* output;
	char* inBuffer;
	char* outBuffer;

	void Dialogmanage();
	void manageSignIn();
	void manageLogIn();
public:
	~Dialog();
	Dialog(Server* server, char* in, char* out);
	void run();
};

