#pragma once
#include "User.h"
#include "UsersControler.h"
#include "Good.h"
#include "GoodsControler.h"
#include "Command.h"
#include "Server.h"
#include "sstream"
#include "textProtocol.h"
using namespace::std;

class Client
{
private:
	string command;
	bool canExit;
	bool needAnswer;
	 enum Command status;
	int step ;
	int ClientTempFlag;
	string tempInfo;
	Good* tempGood;
	idType tempID;
	CMD cmd;
	CMD cmdRecvd;
	idType userID;
	ClientType userType ;
	User* user;
	Text* input;
	Text* output;
	GoodsControler* goods;
	inline	void waitForAnswer();
	inline void sendRequest();
	void clearChacheFiles(const char* ChachePath)const;
	static unordered_map<string, enum Command> Client_Command;
public:
	Client(Text& in,Text& out);
	~Client();
	void ClientMain();
	void whenLogIn();
	void whenLogOut();
	void whenSignIn();
	void whenInfome();
	void whenAddGood();
	void sendRequestWithoutAnswer();
	void whenAskForAllGoods();
	void whenChangeInfo(string cmd);
	void whenShowInfo(string cmd);
};

