     
#include "Controler.h"
#define  _FILE_SAVING_PATH_(id)  ((path + "/" + to_string(id) + ".TBobj").c_str())
#define  _FILE_TEMP_PATH_(id)  ((path + "/" + "source_temp_" + to_string(id) + "_" + to_string(t)).c_str())
//#define RENAME_FILE_ERR




void Controler::getObjectById(idType id, Object*& obj)
{
	AvoidConfictFromSaving
	Object* temp = obj;
	obj=obj->getByPtr( allObjects.find(id)->second);
	temp->deleteByPtr();
	return;
}

set<idType> Controler::getAllID()
{
	AvoidConfictFromSaving
	unordered_map<idType, Object*>::iterator it = allObjects.begin();
	set<idType> IDset;
	while (it != allObjects.end()) {
		IDset.insert(it->first);
		it++;
	}
		return IDset;
}

int Controler::ObjectNum()
{
	return objectNum;
}

bool Controler::contains(idType id)
{
	AvoidConfictFromSaving
	return (allObjects.find(id) != allObjects.end());
}
void Controler::askForSave(idType id)
{
	AvoidConfictFromSaving
	toBeSaved.insert(id);
}
bool Controler::add(istream& input)
{
	Object* objectPtr= NewObject();
	objectPtr=objectPtr->getByStream(input); //getByStream(objectPtr,input);
	return  add(objectPtr);	
}

bool  Controler::readOutFromFiles()
{
	if (autoSave != NULL)return false;
	vector<string> files;
	getFiles(path, files);
	for (string filePath : files) {
		ifstream input(filePath);
		if (input.is_open()) {
			add(input);
			input.close();
		}

	}
	autoSave = new thread(&Controler::saveThread, this);
	return true;
}

bool Controler::rem(idType id)
{
	AvoidConfictFromSaving
	unordered_map<idType,Object*>::iterator it = allObjects.find(id);
	if (it != allObjects.end()) {
		allObjects.find(it->second->id())->second->deleteByPtr();
		allObjects.erase(it);
		if (toBeSaved.find(it->second->id()) != toBeSaved.end())toBeSaved.erase(it->second->id());
		if (toBeRemoved.find(it->second->id()) != toBeRemoved.end())toBeRemoved.erase(it->second->id());
		objectNum--;
	}
	return it != allObjects.end();
}

void Controler::saveThread()
{
	while (1) {
		if (toStopSave)break;
		isAutoSaveSleeping = true;
		this_thread::sleep_for(chrono::minutes(1));
		isAutoSaveSleeping = false;
		if (toBeSaved.empty()&&toBeRemoved.empty())continue;
		if (toStopSave)break;
		else {
			//usingLocker.lock();
			save();
			//usingLocker.unlock();
		}
	}
}

Controler::Controler(string path)
{
	toStopSave = false;
	maxId = 0;
	objectNum = 0;
	this->path = path;
	toBeSaved.clear();
	isAutoSaveSleeping = true;
	autoSave = NULL;
}

Controler:: ~Controler() {
	toStopSave = true;
	if (isAutoSaveSleeping); //pthread_cancel();
	else autoSave->join();
	save();
	unordered_map <idType, Object*>::iterator it = allObjects.begin();
	while (it != allObjects.end()) {
		it->second->deleteByPtr();
		it++;
	}
}



Object* Controler::NewObject()
{
	return nullptr;
}


 int Controler::save()
{
	 AvoidConfictFromSaving
	bool flag[4] = { 0 };
	set<idType>::iterator it = toBeSaved.begin();
	while(it!=toBeSaved.end()) {
		idType id = *it;
		it=toBeSaved.erase(it);
		time_t t; time(&t);
		if (ENOENT != _access(_FILE_SAVING_PATH_(id), 0)) {
			if (0 != rename(_FILE_SAVING_PATH_(id), _FILE_TEMP_PATH_(id))) { flag[0] = 1; };
		}
		ofstream output(_FILE_SAVING_PATH_(id));
		if (output.is_open()) {
			output << (*allObjects.find(id)->second).turnIntoString();//**
			output.close();
		}
		else { flag[1] = 1; }
		if (0 != remove(_FILE_TEMP_PATH_(id))) { flag[2] = 1; }
	}
	
	it = toBeRemoved.begin();
	while(it!=toBeRemoved.end()) {
		it = toBeRemoved.erase(it);
		if (0 != remove(_FILE_SAVING_PATH_(*it))) { flag[3] = 1; }
	}
	return flag[0] + flag[1] * 2 + flag[2] * 4 + flag[3] * 8;
}


void Controler::getFiles(string path, vector<string>& files)
{
	intptr_t hFile = 0;//文件句柄  
	struct _finddata_t fileinfo;//文件信息  
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*.TBobj").c_str(), &fileinfo)) != -1)
		// "\\*"是指读取文件夹下的所有类型的文件，若想读取特定类型的文件，以png为例，则用“\\*.png”
	{
		do
		{
			files.push_back(path + "\\" + fileinfo.name);//加入列表  
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

idType Controler::suggestID()
{
	idType id= maxId+1;
	idType top = maxId;
	while (id != top) {
		if (allObjects.find(id) == allObjects.end())return id;
		maxId++; id++;
	}
	return 0;
}

bool Controler::add(Object* ptr)
{
	AvoidConfictFromSaving
	if (allObjects.find(ptr->id()) != allObjects.end())return false;
	bool ok = allObjects.insert(make_pair(ptr->id(), ptr)).second;
	if (ok) {
		toBeSaved.insert(ptr->id());
		if (toBeRemoved.find(ptr->id()) != toBeRemoved.end())toBeRemoved.erase(ptr->id());
		objectNum++;
		if (ptr->id() > maxId)maxId = ptr->id();
	}
	return true;
}
