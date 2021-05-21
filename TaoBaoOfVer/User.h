#pragma once
#include "Object.h"
#include <string>
#include<sstream>
#include <iostream>
#include <set>
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
	User(string str);
	User(istream& input);
	User(const idType id, const string& code, const string& name);//useless
	bool initUser(idType id,istream &input,ostream& output);
public:
	static bool canBePassword(string code);
	static bool canBeName(string name);
	virtual userType  type()const = 0 ;
	bool changeCode(string code);// { if ()this->code = code; }
	bool changeName(string name);
	int income(moneyType);
	int outcome(moneyType);
	moneyType Money()const;


	virtual Object* getByPtr(Object* obj) = 0;
	virtual Object* getByStream(istream&)=0;
	virtual string turnIntoString()const;
	virtual bool deleteByPtr()=0;
};

class Consumer :
	public User
{
private:
	Consumer(string);
	Consumer(istream&);
public:
	Consumer(idType id);
	Consumer();
	userType type() const;

	virtual Object* getByPtr(Object* obj) ;
	virtual Object* getByStream(istream&);
	virtual string turnIntoString()const ;
	virtual bool deleteByPtr();
};

class Seller :
	public User
{
private:
	set<idType> tradeGoods;
	Seller(string);
	Seller(istream&);
public:
	Seller(idType id);
	Seller();
	userType   type()const;
	bool addGood(idType id);
	bool remGood(idType id);

	virtual Object* getByPtr(Object* obj) ;
	virtual Object* getByStream(istream&);
	virtual string turnIntoString()const;
	virtual bool deleteByPtr();
};

