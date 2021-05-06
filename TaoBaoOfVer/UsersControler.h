#pragma once
#include "User.h"
#include <hash_map>
#include <thread>

using namespace::std;
using namespace::stdext;
class UsersControler
{
private:
	hash_map <idType,User*> allUsers;
	inline bool add(string str);
	inline bool remove(idType id);
	void saveThread();
	UsersControler();
	bool saved;
	inline bool save();
public:
	static UsersControler* instance;
	static UsersControler* getInstance;
};

