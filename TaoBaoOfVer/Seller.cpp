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
	delete this;
	return true;
}
