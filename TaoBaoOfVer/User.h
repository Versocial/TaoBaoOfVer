#pragma once
#include "Object.h"
#include <string>
#include<sstream>
#include <iostream>
#include <set>
#include "Good.h"
#define moneyType unsigned long long
using namespace::std;

 enum userType {
	Type_Consumer, Type_Seller
};

class User :public Object
{
private:
protected:
	string name;
	string password;
	moneyType money;
	User();
	User(idType id, string name,string PassWord);//for signIn
	User(istream& input);// for server
	bool initUser(idType id,istream &input,ostream& output);
public:
	static bool canBePassword(string code);
	static bool canBeName(string name);
	bool matchWithPassWord(string passwd)const;
	virtual userType  type()const = 0 ;
	bool changePassWord(string code);
	bool changeName(string name);
	int income(moneyType);
	int outcome(moneyType);
	moneyType Money()const;
	string Name()const;

	virtual Object* getByStream(istream&)=0;
	virtual string turnIntoString()const;
	virtual bool deleteByPtr()=0;
};

class Consumer :
	public User
{
private:
	Consumer(istream&);// for server
public:
	Consumer();
	Consumer(idType id);// for client
	Consumer(idType ID, string Name, string PassWord);//for signin
	userType type() const;

	virtual Object* getByStream(istream&);
	virtual string turnIntoString()const ;
	virtual bool deleteByPtr();
};

class Seller :
	public User
{
private:
	set<idType> tradeGoods;
	Seller(istream&);
public:
	Seller();
	Seller(idType id);//for client
	Seller(idType ID, string Name, string PassWord);//for signin
	userType   type()const;
	bool addGood(idType id);
	bool deleteGood(idType id);

	virtual Object* getByStream(istream&);
	virtual string turnIntoString()const;
	virtual bool deleteByPtr();
};

