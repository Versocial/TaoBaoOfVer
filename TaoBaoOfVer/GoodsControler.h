#pragma once
#include "Controler.h"
#include "Good.h"
#include <iostream>
using namespace::std;

class GoodsControler:public Controler
{
private:
	virtual Object& theObject();
	virtual string objPostfix();
	static GoodsControler* instanceG;
	GoodsControler(string path);
public:
	idType maxID();
	static GoodsControler* getInstance(string path);
	~GoodsControler();
	bool addOneGoodByCin();// just for test
	void toShowGoods(ostream& input);
};

