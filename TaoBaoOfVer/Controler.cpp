     #include "Controler.h"
#define _FILE_SAVING_PATH_(id)    ((filePath + "/" + to_string(id) + "." + objPostfix()).c_str())
#define _FILE_TEMP_PATH_(id,t)  ((filePath + "/" + "source_temp_" + to_string(id) + "_" + to_string(t)).c_str())

int Controler::deleteFile(idType id)
{
	if (containsInMemory(id))removeFromMemory(id);
	return  remove(_FILE_SAVING_PATH_(id));
}

int Controler::saveFile(idType id)
{
	bool flag[3] = { 0,0,0 };
	if (allObjects.count(id)) {
			if(toBeSaved.count(id))toBeSaved.erase(id);
			time_t t=time(NULL);
			if (containsInFile(id)) {
				if (0 != rename(_FILE_SAVING_PATH_(id), _FILE_TEMP_PATH_(id,t))) { flag[0] = 1; };
			}
			ofstream output(_FILE_SAVING_PATH_(id));
			if (output.is_open()) {
				output << allObjects[id]->turnIntoString();//**
				output.close();
			}
			else { flag[1] = 1; }
			if (0 != remove(_FILE_TEMP_PATH_(id,t))) { flag[2] = 1; }
		}

		return flag[0] + flag[1] * 2 + flag[2] * 4;
}

bool Controler::readFromFile(idType id)
{
	if (allObjects.count(id))return false;
	ifstream input(_FILE_SAVING_PATH_(id));
	if (input.is_open()) {
		allObjects[id] = theObject().getByStream(input);
		input.close();
		return true;
	}
	return false;
}



set<idType> Controler::AllIDInMemory()
{
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
	return allObjects.size();
}

void Controler::releaseFromMemoryIntoFile(idType id)
{
	saveFile(id);
	removeFromMemory(id);
}

bool Controler::containsInMemory(idType id)
{
	//AvoidConfictFromSaving
	return allObjects.count(id);
}
bool Controler::containsInFile(idType id)
{
	return -1 != _access(_FILE_SAVING_PATH_(id), 0);
}
void Controler::askForSave(idType id)
{
	if(!toBeSaved.count(id))	toBeSaved.insert(id);
}
bool Controler::addToMemory(istream& input)
{
	return  addToMemory(theObject().getByStream(input));	
}


bool  Controler::readOutAllFromFile()
{
	//AvoidConfictFromSaving
	vector<string> files=getFiles(filePath);
	for (string filePath : files) {
		ifstream input(filePath);
		if (input.is_open()) {
			addToMemory(input);
			input.close();
		}
	}
	return true;
}



bool Controler::removeFromMemory(idType id)
{
	//AvoidConfictFromSaving
	bool flag = allObjects.count(id);
	if (allObjects.count(id)) { allObjects[id]->deleteByPtr(); allObjects.erase(id); }
	if (toBeSaved.count(id))toBeSaved.erase(id);
	return flag;
}

Controler::Controler(string path)
{
	maxId = 0;
	allObjects.clear();
	toBeSaved.clear();
	this->filePath = path;
}

Controler:: ~Controler() {
	save();
	unordered_map <idType, Object*>::iterator it = allObjects.begin();
	while (it != allObjects.end()) {
		it->second->deleteByPtr();
		it++;
	}
}



 int Controler::save()
{
	 //AvoidConfictFromSaving
	bool flag[4] = { 0 };
	set<idType>::iterator it = toBeSaved.begin();
	while(it!=toBeSaved.end()) {
		idType id = *it;
		it=toBeSaved.erase(it);
		time_t t= time(NULL);
		if (ENOENT != _access(_FILE_SAVING_PATH_(id), 0)) {
			if (0 != rename(_FILE_SAVING_PATH_(id), _FILE_TEMP_PATH_(id,t))) { flag[0] = 1; };
		}
		ofstream output(_FILE_SAVING_PATH_(id));
		if (output.is_open()) {
			output << allObjects[id]->turnIntoString();
			output.close();
		}
		else { flag[1] = 1; }
		if (0 != remove(_FILE_TEMP_PATH_(id,t))) { flag[2] = 1; }
	}
	
	return flag[0] + flag[1] * 2 + flag[2] * 4;
}


 vector<string>& Controler::getFiles(string path)
{
	intptr_t hFile = 0;//文件句柄  
	struct _finddata_t fileinfo;//文件信息  
	string p;
	vector<string>files;
	if ((hFile = _findfirst(p.assign(path).append("\\*."+ objPostfix()).c_str(), &fileinfo)) != -1)
		// "\\*"是指读取文件夹下的所有类型的文件，若想读取特定类型的文件，以png为例，则用“\\*.png”
	{
		do
		{
			files.push_back(path + "\\" + fileinfo.name);//加入列表  
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return files;
}

idType Controler::suggestID()
{
	idType id= maxId+1;
	idType top = maxId;
	while (id != top) {
		if (!allObjects.count(id)&&!containsInFile(id))return id;
		maxId++; id++;
	}
	return _UNVALID_ID;
}

Object* Controler::getObjectInMemory(idType id)
{
	if (!allObjects.count(id))return NULL;
	return allObjects[id];
}

bool Controler::addToMemory(Object* ptr)
{
	//AvoidConfictFromSaving
	if(allObjects.count(ptr->id()))return false;
	bool ok = allObjects.insert(make_pair(ptr->id(), ptr)).second;
	if (ok) {
		toBeSaved.insert(ptr->id());
		if (ptr->id() > maxId)maxId = ptr->id();
	}
	return true;
}
