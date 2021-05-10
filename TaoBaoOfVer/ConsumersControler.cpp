#include "UsersControler.h"
ConsumersControler* ConsumersControler::instanceC = NULL;
ConsumersControler::ConsumersControler(string path):Controler(path)
{
	if (ObjectNum() == 0)maxId = FIRST_CONSUMER_NUMBER;
}
ConsumersControler::~ConsumersControler()
{
	instanceC = NULL;
}
Object* ConsumersControler::NewObject()
{
	return new Consumer();
}
bool ConsumersControler::addCountByCin()
{
	idType id = suggestID();
	if (id == 0) {
		cout << "[ERORR ]: too many counts ! no id for you to join ! Please contact administrator.\n"; return false;
	}
	else return add(new Consumer(id));
}
ConsumersControler* ConsumersControler::getInstance(string path)
{
	if (instanceC == NULL) {
		instanceC = new ConsumersControler(path);
		instanceC->readOutFromFiles();
		return instanceC;
	}
	else return NULL;
}
