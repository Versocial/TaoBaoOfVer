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
	Object(idType id);
	~Object();
public:
	idType id()const;

	virtual Object* getByStream( istream&)=0;
	virtual string turnIntoString()const=0;
	virtual bool deleteByPtr()=0;
};

