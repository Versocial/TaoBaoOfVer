#pragma once
#include "GoodsControler.h"
#include "UsersControler.h"
#include <iostream>
#include "log.h"
//using namespace ::std;

#define ConsumersControlerPath ("../res/Consumer") 
#define GoodsControlerPath ("../res/Good") 
#define SellersControlerPath ("../res/Seller")
#define LogPath ("../res/server.log")

class Server
{
private:
	Logger* logger;
	mutex usingLocker;
	thread* autoSave;
	istream* input;
	ostream* output;
	ConsumersControler* consumers;
	SellersControler* sellers;
	GoodsControler* goods;
	static Server* instance;
	Server(istream& in, ostream& out);
	void serverMain();
	void autoSavingThread();
	void save();
public:
	//int Main1();
	static Server* getInstance(istream&in,ostream& out);
	~Server();
};
