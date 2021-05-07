#include "UsersControler.h"
ConsumersControler* ConsumersControler::instanceC = NULL;
ConsumersControler::ConsumersControler(string path):UsersControler(path)
{
}
ConsumersControler::~ConsumersControler()
{
}
ConsumersControler* ConsumersControler::getInstance(string path)
{
	if (ConsumersControler::instanceC == NULL)return (ConsumersControler::instanceC = new ConsumersControler(path));
	else return NULL;
}

bool ConsumersControler::dispose()
{
	if (ConsumersControler::instanceC != NULL) {
		delete ConsumersControler::instanceC;
		return true;
	}
	else return false;
}