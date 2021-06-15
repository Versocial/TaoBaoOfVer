#include "GoodsControler.h"


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
}

GoodsControler::~GoodsControler()
{
	instanceG = NULL;
}


GoodsControler* GoodsControler::getInstance(string path)
{
	if (instanceG == NULL) { instanceG = new GoodsControler(path); instanceG->readOutAllFromFile();  return instanceG; }
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
