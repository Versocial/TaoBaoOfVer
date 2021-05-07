#include "UsersControler.h"
//#define RENAME_FILE_ERR

bool UsersControler::add(string str)
{
	istringstream input(str);
	return add(input);
}
bool UsersControler::add(istream&input)
{
	User* userPtr;
	unsigned int type; input >> type;
	switch (type)
	{
	case Type_Consumer:userPtr = new Consumer(input); break;
	case Type_Seller:userPtr = new Seller(input); break;
	default: return false;
		break;
	}
	bool ok=allUsers.insert(make_pair((userPtr->id()), userPtr)).second;
	if (ok)toBeSaved.insert(userPtr->id());
	if (toBeRemoved.find(userPtr->id()) != toBeRemoved.end())toBeRemoved.erase(userPtr->id());
	return ok;
}

bool UsersControler::rem(idType id)
{
	unordered_map<idType,User*>::iterator it = allUsers.find(id);
	if (it!=allUsers.end()) {
		switch (it->second->type())
		{
		case Type_Consumer:delete (Consumer*)(it->second);
		case Type_Seller:delete (Seller*)(it->second);
		default:
			break;
		}
		allUsers.erase(it);
		if (toBeSaved.find(it->second->id())!=toBeSaved.end())toBeSaved.erase(it->second->id());
	}	
	return it != allUsers.end();
}

void UsersControler::saveThread()const
{
	while (1) {
		this_thread::sleep_for(chrono::minutes(1));
		if (toBeSaved.empty())continue;
		else save();
	}
}

UsersControler::UsersControler(string path)
{
	this->path = path;
	vector<string> files;
	getFiles1(path, files);
	

}

UsersControler:: ~UsersControler()
{
	save();
}

inline int UsersControler::save()const
{
	bool flag[4] = { 0 };
	for (idType id : toBeSaved) {
		time_t t; time(&t);
		if (ENOENT != _access((path + "/" + to_string(id)).c_str(), 0)) {
			if (0 != rename((path + "/" + to_string(id)).c_str(), (path + "/" + "source_temp_" + to_string(id) + "_" + to_string(t)).c_str())) { flag[0] = 1; };
		}
		ofstream output(path + "/" + to_string(id));
		if (output.is_open()) {
			output << allUsers.find(id)->second->turnIntoString();
			output.close();
		}
		else { flag[1] = 1; }
		if (0 != remove((path + "/" + "source_temp_" + to_string(id) + "_" + to_string(t)).c_str())) { flag[2] = 1; }
	}
	for (idType id : toBeRemoved) {
		if (0 != remove((path + "/"+ to_string(id) ).c_str())) { flag[3] = 1; }
	}
	return flag[0] + flag[1]*2+flag[2]*4+flag[3]*8;
}

UsersControler* UsersControler::getInstance(string path)
{
	return nullptr;
}
