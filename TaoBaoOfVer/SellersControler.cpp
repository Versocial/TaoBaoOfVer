#include "UsersControler.h"

SellersControler* SellersControler::instanceS(NULL);
SellersControler::~SellersControler()
{
}

SellersControler* SellersControler::getInstance(string path)
{
	return SellersControler::instanceS;
}
