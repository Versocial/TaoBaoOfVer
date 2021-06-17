#pragma once
#include "Controler.h"
#include "Good.h"
#include <iostream>
using namespace::std;

class GoodsControler:public Controler
{
private:
	static  idType startId;
	virtual Object& theObject();
	virtual string objPostfix();
	static GoodsControler* instanceG;
	GoodsControler(string path);
public:
	idType startID();
	idType maxID();
	static GoodsControler* getInstance(string path);
	~GoodsControler();
	bool addOneGoodByCin();// just for test
	void toShowGoods(ostream& output);
};

