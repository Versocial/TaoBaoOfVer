#include "User.h"

Consumer::Consumer(idType id) :User() 
{
	initUser(id);
}

Consumer::Consumer(string info):User(info)
{
}

Consumer::Consumer(istream& input):User(input)
{
}

Consumer::Consumer(): User()
{
}

userType Consumer::type()const
{
	return Type_Consumer;
}

Object* Consumer::getByStream(istream& input)
{
	Consumer* consumer = new Consumer(input);
	return consumer;
}

string Consumer::turnIntoString() const
{
	return " " + to_string(ID) + " " + password + " " + " " + to_string(money) + " " + name + " ";

}

bool Consumer::deleteByPtr()
{
	delete this;
	return false;
}
