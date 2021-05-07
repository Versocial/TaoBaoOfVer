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
	idType maxId;
	int objectNum;
	string path;
	unordered_map <idType, Object*> allObjects;
	thread* autoSave;
	bool toStopSave;
	bool rem(idType id);
	void saveThread();
	set<idType> toBeSaved;
	set<idType> toBeRemoved;
	int save();
	static void getFiles(string path, vector<string>& files);
protected:
	Controler(string path);
	~Controler();
	bool add(istream& input);
	virtual bool getByStream(Object*&, istream&)const;
	virtual string turnIntoString(const Object&)const;
	virtual bool deleteByPtr(Object*)const;
public:
	virtual bool add(string str);
	//virtual Object getCopyById(idType id);
	//virtual Object* getPtrById(idType id);
	bool contains(idType id);
	void askForSave(idType id);
	
	
};
