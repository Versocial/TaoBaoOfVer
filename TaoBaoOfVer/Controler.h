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

//#define AvoidConfictFromSaving  ; lock_guard<mutex> temp_lock_guard(Controler::usingLocker);
//#define 
class Controler
{
private:
	static Object* _the_Object;
	int objectNum;
	string path;
	unordered_map <idType, Object*> allObjects;
	bool rem(idType id);
	set<idType> toBeSaved;
	 void getFiles(string path, vector<string>& files);
	bool add(istream& input);
	Object* theObject();
protected:

	virtual string objPostfix()=0;
	idType maxId;
	idType suggestID();
	bool add(Object* ptr);
	Controler(string path);
	~Controler();
	virtual Object* NewObject();
public:
	void askForSave(idType id);
	int deleteObject(idType id);
	int saveObject(idType id);
	bool readFromFile(idType id);
	bool releaseIntoFile(idType id);
	void getObjectById(idType id,Object*& obj);
	set<idType> getAllID();
	int ObjectNum();
	bool contains(idType id);
	bool readOutAllObjects();
	bool readOutAllIDs();
	int save();
	/*Object* getControlOf(idType id);
	void releaseControle();
	*/
};
