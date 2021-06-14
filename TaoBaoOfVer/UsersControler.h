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


class ConsumersControler :
	public Controler
{
private:
	virtual Object& theObject();
	virtual string objPostfix();
	ConsumersControler(string path);
	static ConsumersControler* instanceC;
public:
	~ConsumersControler();
	bool addCountByCin();//just for test
	static  ConsumersControler* getInstance(string path);
	//void LogIn(idType id);
	//void LogOut(idType id);
};


class SellersControler :
	public Controler
{
private:
	virtual Object& theObject();
	virtual string objPostfix();
	SellersControler(string path);
	static SellersControler* instanceS;
public:
	~SellersControler();
	bool addCountByCin();//just for test
	static  SellersControler* getInstance(string path);
};


