#pragma once
#define  define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "User.h"
#include "UsersControler.h"
#include "Good.h"
#include "GoodsControler.h"
#include "Command.h"
#include "Server.h"
#include "sstream"
#include "textProtocol.h"
#include "OrdersControler.h"

#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")

class Client
{
private:
	string command;
	bool canExit;
	bool needAnswer;
	 enum Command status;
	 SOCKET sock;
	int step ;
	int ClientTempFlag;
	string tempInfo;
	Good* tempGood;
	GoodNumber tempNumber;
	idType tempID;
	moneyType tempPrice;
	CMD cmd;
	CMD cmdRecvd;
	idType userID;
	ClientType userType ;
	User* user;
	Text* input;
	Text* output;
	GoodsControler* goods;
	OrdersControler* shopCar;
	OrdersControler* orders;
	inline	void waitForAnswer();
	inline void sendRequest();
	void clearChacheFiles(const char* ChachePath)const;
	static unordered_map<string, enum Command> Client_Command;
public:
	Client(Text& in,Text& out);
	~Client();
	void ClientMain();
	void sendRequestWithoutAnswer();
	void whenLogIn();
	void whenLogOut();
	void whenSignIn();
	void whenInfome();
	void whenAddGood();
	void whenAskForAllGoods();
	void whenChangeInfo(string cmd);
	void whenShowInfo(string cmd);
	void whenCooseGood();
	void whenShowOrder();
	void whenManageOrder();
	void whenManagePullSold();
	void whenShowSold();
	void whenManageDiscount();
	void pullTarget();

	Good* pullTarget(idType id);
	void pullTarget_send(idType id);
	Good* pullTarget_recv(idType id);
};
//hou tai din shi la qu

