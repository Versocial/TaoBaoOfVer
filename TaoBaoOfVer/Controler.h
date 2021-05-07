#pragma once
#include "Object.h"
#include <unordered_map>
#include <thread>
#include<set>
#include<sstream>
#include<fstream>
#include<io.h>

using namespace::std;
using namespace::stdext;
class Controler
{
private:
	static Controler* instance;
	idType maxId;
	int objectNum;
	string path;
	unordered_map <idType, Object*> allObjects;
	thread* autoSave;
	bool toStopSave;
	bool add(istream& input);
	bool rem(idType id);
	void saveThread();
	Controler(string path);
	~Controler();
	set<idType> toBeSaved;
	set<idType> toBeRemoved;
	inline int save()const;
	static void getByLine(Object*&,istream&);
	static string turnIntoLine(const Object&);
	static	void deleteByPtr(Object*);
	static void getFiles(string path, vector<string>& files);
public:
	bool add(string str);
	static Controler* getInstance(string path);
	static bool dispose();
};

Controler* Controler::instance(NULL);

