#include "UsersControler.h"

SellersControler* SellersControler::instanceS(NULL);
SellersControler::~SellersControler()
{
	instanceS = NULL;
}

bool SellersControler::addCountByCin()
{
	idType id = suggestID();
	if (id == 0) { cout << "[ERORR ]: too many seller counts ! no id for you to join ! Please contact administrator.\n"; return false; }
	cout << ">> Seller initializing :\n";
	return add(new Seller(id));
}

Object& SellersControler::theObject()
{
	static Seller seller;
	return seller;
}

string SellersControler::objPostfix()
{
	return "TBseller";
}

SellersControler::SellersControler(string path) :Controler( path)
{
	if (ObjectNum() == 0)maxId = FIRST_CONSUMER_NUMBER;
	_the_Object = new Seller();
}

SellersControler* SellersControler::getInstance(string path)
{
	if (instanceS == NULL) {
		instanceS = new SellersControler(path);
		instanceS->readOutAllIDs();
		return instanceS;
	}
	else return NULL;
}
