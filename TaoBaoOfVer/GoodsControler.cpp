#include "GoodsControler.h"


GoodsControler* GoodsControler::instanceG = NULL;
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

Object* GoodsControler::NewObject()
{
	return new Good();
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
	if (instanceG == NULL) { instanceG = new GoodsControler(path); instanceG->readOutAllObjects();  return instanceG; }
	else return NULL;
}

bool GoodsControler::addByCin()
{
	idType id = suggestID();
	if (id == 0) {
		cout << "[ERORR ]: too many goods ! no id for another good ! Please contact administrator.\n"; return false;
	}
	return add(new Good(id));
}

void GoodsControler::toShowGoods(ostream&input)
{
	input << "All Goods :\n";
	Object* good = new Good();
	for (idType id : getAllID()) {
		getObjectById(id, good);
		input<< ((Good*)good)->toShow()<<endl;
	}
	delete (Good*)good;
}
