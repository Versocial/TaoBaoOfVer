#pragma once
#include "User.h"
#include <unordered_map>
#include <thread>
#include<set>
#include<sstream>
#include<fstream>

#include<io.h>

using namespace::std;
using namespace::stdext;
class UsersControler
{
private:
	idType maxUserId;
	int userNum;
	string path;
	unordered_map <idType,User*> allUsers;
	 bool add(string str);
	 bool add(istream&input);
	 bool rem(idType id);
	void saveThread()const;
	UsersControler(string path);
	~UsersControler();
	set<idType> toBeSaved;
	set<idType> toBeRemoved;
	inline int save()const;
public:
	static UsersControler* instance;
	static UsersControler* getInstance(string path);
};

