#include "Client.h"
#include "Server.h"
#include<iostream>
#define ConsumersControlerPath ("../res/Consumer") 
#define GoodsControlerPath ("../res/Good") 
using namespace::std;

int main() {
	//ConsumersControler* C_Controler=ConsumersControler::getInstance(ConsumersControlerPath);
	//GoodsControler* G_Controler = GoodsControler::getInstance(GoodsControlerPath);
	//G_Controler->toShowGoods(cout);
	//G_Controler->addByCin();
	////G_Controler->toShowGoods(cout);
	//delete C_Controler;
	//delete G_Controler;

	Server* server = Server::getInstance(cin,cout);
	server->Main1();


}
/*0 10001 vvv 0  evpeople*/