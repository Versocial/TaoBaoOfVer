#include "User.h"

Consumer::Consumer(idType id) :User() 
{
	initUser(id,cin,cout);
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

Object* Consumer::getByPtr(Object* obj)
{
	return new Consumer(*(Consumer*)obj);
}

Object* Consumer::getByStream(istream& input)
{
	Consumer* consumer = new Consumer(input);
	return consumer;
}

string Consumer::turnIntoString() const
{
	return User::turnIntoString();

}

bool Consumer::deleteByPtr()
{
	delete this;
	return true;
}
