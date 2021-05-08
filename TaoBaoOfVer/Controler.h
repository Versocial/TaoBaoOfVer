#pragma once
#include "Object.h"
#include <unordered_map>
#include <thread>
#include<set>
#include<sstream>
#include<fstream>
#include<io.h>
#include<mutex>

using namespace::std;
using namespace::stdext;

#define AvoidConfictFromSaving  ; lock_guard<mutex> temp_lock_guard(Controler::usingLocker);
class Controler
{
private:
	idType maxId;
	int objectNum;
	string path;
	unordered_map <idType, Object*> allObjects;
	thread* autoSave;
	bool toStopSave;
	bool isAutoSaveSleeping;
	bool rem(idType id);
	void saveThread();
	set<idType> toBeSaved;
	set<idType> toBeRemoved;
	int save();
	static void getFiles(string path, vector<string>& files);
protected:
	mutex usingLocker;
	Controler(string path);
	~Controler();
	virtual bool getByStream(Object*&, istream&)const;
	virtual string turnIntoString(const Object&)const;
	virtual bool deleteByPtr(Object*)const;
public:
	virtual bool add(string str);
	bool add(istream& input);
	//virtual Object getCopyById(idType id);
	//virtual Object* getPtrById(idType id);
	bool contains(idType id);
	void askForSave(idType id);
	
	
};
