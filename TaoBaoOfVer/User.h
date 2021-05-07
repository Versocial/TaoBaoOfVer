#pragma once
#include "Object.h"
#include <string>
#include<sstream>
#define moneyType unsigned long long

 enum userType {
	Type_Consumer, Type_Seller
};

class User :public Object
{
private:
	string name;
	string code;
	moneyType money;
	static bool canBeCode(string code);
	static bool canBeName(string name);
protected:
	User(string str);
	User(istream& input);
public:
	virtual userType  type()const = 0 ;
	bool changeCode(string code);// { if ()this->code = code; }
	bool changeName(string name);
	int income(moneyType);
	int outcome(moneyType);
	string turnIntoString()const;
	moneyType Money()const;
};

class Consumer :
	public User
{
public:
	Consumer(string);
	Consumer(istream&);
	userType type() const;

};

class Seller :
	public User
{
public:
	Seller(string);
	Seller(istream&);
	userType   type()const;
};

