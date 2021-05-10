#include "UsersControler.h"

SellersControler* SellersControler::instanceS(NULL);
SellersControler::~SellersControler()
{
	instanceS = NULL;
}

SellersControler::SellersControler(string path) :Controler( path)
{

}

SellersControler* SellersControler::getInstance(string path)
{
	if (instanceS == NULL) {
		instanceS = new SellersControler(path);
		return instanceS;
	}
	else return NULL;
}
