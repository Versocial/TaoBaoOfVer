#include "Client.h"
#define ConsumersControlerPath ("../res/Consumer") 

int main() {
	ConsumersControler* C_Controler=ConsumersControler::getInstance(ConsumersControlerPath);
	int i = 0;
	int j = 0;
	//string temp;
	//cin >> temp;
	//Consumer c(temp);
	C_Controler->addCountByCin();
	//cin >> temp;
	delete C_Controler;
}
/*0 10001 vvv 0  evpeople*/