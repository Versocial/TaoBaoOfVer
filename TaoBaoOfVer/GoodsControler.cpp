#include "GoodsControler.h"
#define FIRST_CONSUMER_NUMBEROFGOODS 1

GoodsControler* GoodsControler::instanceG = NULL;
Object& GoodsControler::theObject()
{
	static Good good;
	return good;
}
string GoodsControler::objPostfix()
{
	return "TBgood";
}
GoodsControler::GoodsControler(string path) :Controler(path)
{
	if (ObjectNum() == 0)maxId = FIRST_CONSUMER_NUMBEROFGOODS;
}

GoodsControler::~GoodsControler()
{
	instanceG = NULL;
}


idType GoodsControler::maxID()
{
	return maxId;
}

GoodsControler* GoodsControler::getInstance(string path)
{
	if (1/*instanceG == NULL*/) { instanceG = new GoodsControler(path); instanceG->readOutAllFromFile();  return instanceG; }
	else return NULL;
}

bool GoodsControler::addOneGoodByCin()
{
	idType id = suggestID();
	if (id == 0) {
		cout << "[ERORR ]: too many goods ! no id for another good ! Please contact administrator.\n"; return false;
	}
	return addToMemory(new Good(id));
}

void GoodsControler::toShowGoods(ostream&output)
{
	output << "All Goods :\n";
	for (idType id : AllIDInMemory()) {
		output<< ((Good*)getObjectInMemory(id))->toShow()<<endl;
	}
}
