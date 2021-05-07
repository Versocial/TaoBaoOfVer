#include "User.h"

Seller::Seller(string info):User(info)
{
	
}

Seller::Seller(istream& input):User(input)
{

}

userType Seller::type() const
{
	return Type_Seller;
}