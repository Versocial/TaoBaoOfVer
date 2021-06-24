#pragma once
#include<string>
#include<iostream>
#define idType unsigned long
#define _INVALID_ID 0

using namespace::std;
class Object
{
private:
protected:
	idType ID;
	Object();
	Object(idType id);
	~Object();
protected:
	void setID(idType id);
public:
	idType id()const;
	virtual Object* getByStream( istream&)=0;//read from string 
	virtual string turnIntoString()const=0;//wirte into string
	virtual bool deleteByPtr()=0;//delete this
};

