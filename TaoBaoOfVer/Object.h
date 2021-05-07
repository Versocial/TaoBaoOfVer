#pragma once
#include<string>
#define idType unsigned long
using namespace::std;
class Object
{
private:
protected:
	idType ID;
public:
	Object(string str);
	Object(istream& input);
	virtual string turnIntoString()const;
	idType id()const;
	//virtual unsigned int type()const = 0;
};

