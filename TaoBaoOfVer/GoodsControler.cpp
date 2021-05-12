#include "GoodsControler.h"

GoodsControler* GoodsControler::instanceG = NULL;
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

GoodsControler* GoodsControler::getInstance(string path)
{
	if (instanceG == NULL) { instanceG = new GoodsControler(path); instanceG->readOutFromFiles();  return instanceG; }
	else return NULL;
}
