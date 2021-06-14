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
#define _UNVALID_ID 0

class Controler
{
private:
	//filePath
	string filePath;
	inline const char* _FILE_SAVING_PATH_(idType id);
	inline const char* _FILE_TEMP_PATH_(idType id, time_t t);
	vector<string>& getFiles(string path);
	//Memory
	unordered_map <idType, Object*> allObjects;//core Memory
	bool addToMemory(istream& input);//add to Memory
	//Auto Save
	set<idType> toBeSaved;//need auto save
	//Id suggest
	idType maxId;
	
protected:
	//filePath
	virtual string objPostfix() = 0;
	//controling Type 
	virtual Object& theObject()=0;// controling Type;
	//Id suggest
	idType suggestID();
		//..
	Controler(string path);
	~Controler();

public:;
	 //File
	  int deleteFile(idType id);// delete File
	  int saveFile(idType id);// save File
	  bool readFromFile(idType id);// read File
	  bool readOutAllFromFile();//read all File
	  bool containsInFile(idType id);// if File has id
	 //Memory
	  bool removeFromMemory(idType id);//remove from Memory
	 bool addToMemory(Object* ptr);// add toMemory (just Memory not file, but ask for save)
	 bool containsInMemory(idType id);// if Memory has id 
	 set<idType>& AllIDInMemory();//all IDs in Memory
	 //Auto Save
	 void askForSave(idType id);//remember to saveing
	 int save();
	 //get test
	int ObjectNum();//size of all Objects
	void releaseFromMemoryIntoFile(idType id);
};
