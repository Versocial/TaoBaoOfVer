#include "User.h"

Seller::Seller(string info)
{
	turnFromString(info);
}

Seller::Seller(istream& input)
{
	turnFromStream(input);
}

userType Seller::type() const
{
	return Type_Seller;
}