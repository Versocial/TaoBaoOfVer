#include "User.h"


Seller::Seller(istream& input):User(input)
{

}

Seller::Seller(idType id)
{
	initUser(id,cin,cout);
}

Seller::Seller(idType ID, string Name,string Password):User(ID,Name,Password)
{
}

Seller::Seller():User()
{
}

userType Seller::type() const
{
	return Type_Seller;
}

bool Seller::addGood(idType id)
{
	if (!tradeGoods.count(id)) { tradeGoods.insert(id); return true; }
	return false;
}

bool Seller::deleteGood(idType id)
{
	if (tradeGoods.count(id)) { tradeGoods.erase(id); return true; }
	return false;
}


Object* Seller::getByStream(istream& input)
{
	return new Seller(input);
}

string Seller::turnIntoString() const
{
	return User::turnIntoString();
}

bool Seller::deleteByPtr()
{
	if(this!=NULL)delete this;
	return true;
}
