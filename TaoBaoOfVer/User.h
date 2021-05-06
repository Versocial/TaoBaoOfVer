#pragma once
#include <string>
using namespace::std;

class User
{
private:
	string name;
	unsigned long ID;
	string code;
	unsigned long long money;
	static bool canBeCode(string code);
	static bool canBeName(string name);
public:
	virtual string  type()const = 0 ;
	bool changeCode(string code);// { if ()this->code = code; }
	bool changeName(string name);
	int income(unsigned int);
	int outcome(unsigned int);
	string turnIntoString()const;
	string turnFromString(string str);
};

class Consumer :
	public User
{
public:
	Consumer(string);
	string  type()const;
};

class Seller :
	public User
{
public:
	Seller(string);
	string  type()const;
};

