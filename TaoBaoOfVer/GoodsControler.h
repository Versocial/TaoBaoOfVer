#pragma once
#include "Controler.h"
#include "Good.h"
#include <iostream>
using namespace::std;

class GoodsControler:public Controler
{
private:
	virtual string objPostfix();
	static GoodsControler* instanceG;
	GoodsControler(string path);
	virtual Object* NewObject();
public:
	static GoodsControler* getInstance(string path);
	~GoodsControler();
	bool addByCin();
	void toShowGoods(ostream& input);
};

