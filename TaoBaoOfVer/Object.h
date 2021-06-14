#pragma once
#include<string>
#include<iostream>
#define idType unsigned long
using namespace::std;
class Object
{
private:
protected:
	idType ID;
	Object();
	Object(idType id);
	~Object();
public:
	idType id()const;
	//friend virtual istream& operator>>(istream& in,Object&obj)=0;
	//friend virtual ostream& operator<<(ostream& out, Object& obj) = 0;
	virtual Object* getByStream( istream&)=0;//read from string 
	virtual string turnIntoString()const=0;//wirte into string
	virtual bool deleteByPtr()=0;//delete this
};

