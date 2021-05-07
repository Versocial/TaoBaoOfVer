#pragma once
#include<string>
#define idType unsigned long
using namespace::std;
class Object
{
private:
	idType ID;
protected:
	
public:
	Object(string str);
	Object(istream& input);
	virtual string turnIntoString()const;
	idType id()const;
};

