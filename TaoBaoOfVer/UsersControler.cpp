#include "UsersControler.h"
#include<sstream>

inline bool UsersControler::add(string str)
{
	User* userPtr;
	istringstream input(str);
	unsigned int type; input>>type;
	switch (type)
	{
	case Type_Consumer:userPtr = new Consumer(input); break;
	case Type_Seller:userPtr = new Seller(input); break;
	default:
		break;
	}
	return allUsers.insert(make_pair((userPtr->id()),userPtr)).second;
}

inline bool UsersControler::remove(idType id)
{
	hash_map<idType,User*>::iterator it = allUsers.find(id);
	if (it!=allUsers.end()) {
		switch (it->second->type())
		{
		case Type_Consumer:delete (Consumer*)(it->second);
		case Type_Seller:delete (Seller*)(it->second);
		default:
			break;
		}
	}	
	return it != allUsers.end();
}

void UsersControler::saveThread()
{
	while (1) {
		this_thread::sleep_for(chrono::minutes(1));
		if (saved)continue;
		else save();
	}
}

UsersControler::UsersControler()
{
	
}

inline bool UsersControler::save()
{
	return false;
}
