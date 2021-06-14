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

//
//Good GoodsControler::getById(idType id)
//{
//	if (!contains(id))return NULL;
//	Good* goodPtr;// = (Good*)getPtrById(id);
//	AvoidConfictFromSaving
//		return *(Good*)goodPtr;
//}


GoodsControler* GoodsControler::getInstance(string path)
{
	if (instanceG == NULL) { instanceG = new GoodsControler(path); instanceG->readOutAllFromFile();  return instanceG; }
	else return NULL;
}

bool GoodsControler::addByCin()
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
	Object* good = new Good();
	for (idType id : AllIDInMemory()) {
		getObjectById(id, good);
		output<< ((Good*)good)->toShow()<<endl;
	}
	delete (Good*)good;
}
