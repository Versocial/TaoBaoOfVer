#include "User.h"

Consumer::Consumer(string info)
{
	turnFromString(info)
}

Consumer::Consumer(istream& input)
{
	turnFromStream(input);
}

userType Consumer::type()const
{
	return Type_Consumer;
}
