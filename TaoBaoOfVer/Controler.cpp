#include "Controler.h"
//#define RENAME_FILE_ERR

bool Controler::add(string str)
{	
	//AvoidConfictFromSaving
	istringstream input(str);
	return add(input);
	
}
/*
Object Controler::getCopyById(idType id)
{
		return *(allObjects.find(id)->second);
}
Object* Controler::getPtrById(idType id)
{
	return nullptr;
}
*/
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
	AvoidConfictFromSaving
	Object* objectPtr;
	getByStream(objectPtr,input);
	bool ok = allObjects.insert(make_pair((objectPtr->id()), objectPtr)).second;
	if (ok) {
		toBeSaved.insert(objectPtr->id());
		if (toBeRemoved.find(objectPtr->id()) != toBeRemoved.end())toBeRemoved.erase(objectPtr->id());
		objectNum++;
		if (objectPtr->id() > maxId)maxId = objectPtr->id();
	}
	return ok;
}

bool Controler::rem(idType id)
{
	AvoidConfictFromSaving
	unordered_map<idType,Object*>::iterator it = allObjects.find(id);
	if (it != allObjects.end()) {
		deleteByPtr(allObjects.find(it->second->id())->second);
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

}

Controler:: ~Controler()
{
	toStopSave = true;
	if (isAutoSaveSleeping); //pthread_cancel();
	else autoSave->join();
	save();
	unordered_map <idType, Object*>::iterator it=allObjects.begin();
	while(it!=allObjects.end()) {
		deleteByPtr(it->second);
		it ++;
	}
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
		if (ENOENT != _access((path + "/" + to_string(id)+".TBobj").c_str(), 0)) {
			if (0 != rename((path + "/" + to_string(id)).c_str(), (path + "/" + "source_temp_" + to_string(id) + "_" + to_string(t)).c_str())) { flag[0] = 1; };
		}
		ofstream output(path + "/" + to_string(id) + ".TBobj");
		if (output.is_open()) {
			output << turnIntoString(*allObjects.find(id)->second);
			output.close();
		}
		else { flag[1] = 1; }
		if (0 != remove((path + "/" + "source_temp_" + to_string(id) + "_" + to_string(t)).c_str())) { flag[2] = 1; }
	}
	
	it = toBeRemoved.begin();
	while(it!=toBeRemoved.end()) {
		idType id = *it;
		it = toBeRemoved.erase(it);
		if (0 != remove((path + "/" + to_string(id)).c_str())) { flag[3] = 1; }
	}
	return flag[0] + flag[1] * 2 + flag[2] * 4 + flag[3] * 8;
}


bool Controler::getByStream(Object*&ptr,istream&input)const
{
	ptr = NULL;//new Object();
	return true;
}

string Controler::turnIntoString(const Object& ptr)const
{
	return ptr.turnIntoString();
}

bool Controler::deleteByPtr(Object* ptr)const
{
	delete (Object*)ptr;
	return true;
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

