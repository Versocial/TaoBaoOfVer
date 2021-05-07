#include "User.h"

Consumer::Consumer(string info):User(info)
{
}

Consumer::Consumer(istream& input):User(input)
{
}

userType Consumer::type()const
{
	return Type_Consumer;
}
