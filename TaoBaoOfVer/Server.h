#pragma once
#include "GoodsControler.h"
#include "UsersControler.h"
#include "log.h"
#include "Command.h"
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
	Server(istream& in, ostream& out);
	void serverMain();
	void autoSavingThread();
	void save();
public:
	ConsumersControler* consumers;
	SellersControler* sellers;
	GoodsControler* goods;
	int Main1();
	static Server* getInstance(istream&in,ostream& out);
	~Server();
};

class Dialog {
private:
	Command status ;
	int step ;
	CMD cmd;
	idType userID;
	ClientType userType ;
	 Server* server;
	 User* user;
	 istream* input;
	 ostream* output;

	 void Dialogmanage();
	 void manageSignIn();
	 void manageLogIn();
public:
	Dialog(Server* server,istream*in,ostream*out);
};
