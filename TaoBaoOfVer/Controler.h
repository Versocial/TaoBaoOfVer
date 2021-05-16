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
//#define 
class Controler
{
private:
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
	bool add(istream& input);
	mutex usingLocker;
protected:
	idType maxId;
	idType suggestID();
	bool add(Object* ptr);
	Controler(string path);
	~Controler();
	virtual Object* NewObject();
public:
	void getObjectById(idType id,Object*& obj);
	set<idType> getAllID();
	int ObjectNum();
	bool contains(idType id);
	void askForSave(idType id);
	bool readOutFromFiles();
	
	
};
