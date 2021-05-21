#pragma once
#include "User.h"
#include "Controler.h"
#include <unordered_map>
#include <thread>
#include<set>
#include<sstream>
#include<fstream>
#include<io.h>

#define FIRST_CONSUMER_NUMBER 10000

using namespace::std;
using namespace::stdext;

//class UsersControler:public Controler
//{
//private:
//protected:
//	UsersControler(string path) ;
//	~UsersControler();
//public:
//};

class ConsumersControler :
	public Controler
{
private:
	virtual string objPostfix();
	ConsumersControler(string path);
	static ConsumersControler* instanceC;
	virtual Object* NewObject();
public:
	~ConsumersControler();
	bool addCountByCin();
	static  ConsumersControler* getInstance(string path);
	void LogIn(idType id);
	void LogOut(idType id);
};


class SellersControler :
	public Controler
{
private:
	virtual string objPostfix();
	SellersControler(string path);
	static SellersControler* instanceS;
	virtual Object* NewObject();
public:
	~SellersControler();
	bool addCountByCin();
	static  SellersControler* getInstance(string path);
};


