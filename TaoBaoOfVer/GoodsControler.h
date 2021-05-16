#include "Controler.h"
#include "Good.h"
#include <iostream>
using namespace::std;

class GoodsControler:public Controler
{
private:
	static GoodsControler* instanceG;
	GoodsControler(string path);
	virtual Object* NewObject();
public:
	static GoodsControler* getInstance(string path);
	~GoodsControler();
	bool addByCin();
	void toShowGoods(ostream& input);
};

