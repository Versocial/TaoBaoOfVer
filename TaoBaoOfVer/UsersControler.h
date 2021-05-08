#pragma once
#include "User.h"
#include "Controler.h"
#include <unordered_map>
#include <thread>
#include<set>
#include<sstream>
#include<fstream>
#include<io.h>

using namespace::std;
using namespace::stdext;
class UsersControler:public Controler
{
private:
protected:
	UsersControler(string path) ;
	~UsersControler();
	virtual bool getByStream(Object*&, istream&)const;
	virtual string turnIntoString(Object&)const;
	virtual bool deleteByPtr(Object*)const;
public:
};

class ConsumersControler :
	public UsersControler
{
private:
	ConsumersControler(string path);
	static ConsumersControler* instanceC;
public:
	~ConsumersControler();
	static  ConsumersControler* getInstance(string path);
	static bool dispose();

};


class SellersControler :
	public UsersControler
{
private:
	SellersControler(string path);
	static SellersControler* instanceS;
public:
	~SellersControler();
	static  SellersControler* getInstance(string path);
	static bool dispose();
	
};


