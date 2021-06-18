#include "GoodsControler.h"

idType GoodsControler::startId=100;

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
	if (ObjectNum() == 0)maxId = startID();
}

GoodsControler::~GoodsControler()
{
	instanceG = NULL;
}


idType GoodsControler::startID()
{
	return startId;
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

bool GoodsControler::addOneGoodByCin()//just for test
{
	idType id = suggestID();
	if (id == 0) {
		cout << "[ERORR ]: too many goods ! no id for another good ! Please contact administrator.\n"; return false;
	}
	return addToMemory(Good::newGood(cin));
}

void GoodsControler::toShowGoods(ostream&output)
{
	output << "All Goods :\n";
	set<idType>allID; AllIDInMemory(allID);
	for (idType id :allID) {
		output<< ((Good*)getObjectInMemory(id))->toShow()<<endl;
	}
}
