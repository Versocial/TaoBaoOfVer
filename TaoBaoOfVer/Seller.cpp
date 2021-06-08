#include "User.h"

Seller::Seller(string info):User(info)
{
	
}

Seller::Seller(istream& input):User(input)
{

}

Seller::Seller(idType id)
{
	initUser(id,cin,cout);
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
	if (tradeGoods.find(id) == tradeGoods.end()) { tradeGoods.insert(id); return true; }
	return false;
}

bool Seller::remGood(idType id)
{
	if (tradeGoods.find(id) != tradeGoods.end()) { tradeGoods.erase(id); return true; }
	return false;
}

Object* Seller::getByPtr(Object* obj)
{
	return new Seller(*(Seller*)obj);
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
