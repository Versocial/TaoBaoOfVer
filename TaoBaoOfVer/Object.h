#pragma once
#include<string>
#define idType unsigned long
using namespace::std;
class Object
{
private:
protected:
	idType ID;
	Object();
public:
	Object(idType id);
	virtual string turnIntoString()const;
	idType id()const;
	//virtual unsigned int type()const = 0;
};

