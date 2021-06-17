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

class Controler
{
private:
	//filePath
	string filePath;
	vector<string> getFiles(string path);
	//Memory
	unordered_map <idType, Object*> allObjects;//core Memory
	bool addToMemory(istream& input);//add to Memory
	//Auto Save
	set<idType> toBeSaved;//need auto save
	
	
protected:
	//filePath
	virtual string objPostfix() = 0;
	//controling Type 
	virtual Object& theObject()=0;// controling Type;
	//Id suggest
	idType maxId;
	//..
	Controler(string path);
	~Controler();

public:;
	 //File
	  int deleteFile(idType id);// delete File
	  int saveFile(idType id);// save File
	  Object* readFromFile(idType id);// read File
	  bool readOutAllFromFile();//read all File
	  bool containsInFile(idType id);// if File has id
	 //Memory
	  Object* getObjectInMemory(idType id);
	  bool removeFromMemory(idType id);//remove from Memory
	 bool addToMemory(Object* ptr);// add toMemory (just Memory not file, but ask for save)
	 bool containsInMemory(idType id);// if Memory has id 
	 set<idType> AllIDInMemory();//all IDs in Memory
	 //Auto Save
	 void askForSave(idType id);//remember to saveing
	 int save();
	 //get test
	int ObjectNum();//size of all Objects
	void releaseFromMemoryIntoFile(idType id);
	//suggestId
	idType suggestID();
};
