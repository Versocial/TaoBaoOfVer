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

string SellersControler::objPostfix()
{
	return "TBseller";
}

SellersControler::SellersControler(string path) :Controler( path)
{

}

Object* SellersControler::NewObject()
{
	return new Seller();
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
