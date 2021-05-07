#include "UsersControler.h"
//#define RENAME_FILE_ERR

UsersControler::UsersControler(string path) :Controler(path)
{
}

UsersControler::~UsersControler()
{
}

bool UsersControler::getByStream(Object*& userPtr, istream& input) const
{
	unsigned int type; input >> type;
	switch (type)
	{
	case Type_Consumer:userPtr = new Consumer(input); break;
	case Type_Seller:userPtr = new Seller(input); break;
	default: return false;
		break;
	}
	return true;
}

string UsersControler::turnIntoString(Object& userPtr) const
{
	User* temp = dynamic_cast<User*>(&userPtr);
	if (temp == NULL)return "FATAL_TURN_INTO_LINE\n";
	return to_string(temp->type()) + userPtr.turnIntoString();
	
}

bool UsersControler::deleteByPtr(Object*objPtr) const
{
	User* userPtr = dynamic_cast<User*>(objPtr);
	switch (userPtr->type())
	{
	case Type_Consumer:delete (Consumer*)userPtr ; break;
	case Type_Seller:delete(Seller*)userPtr; break;
	default: return false;
		break;
	}
	return true;
}

