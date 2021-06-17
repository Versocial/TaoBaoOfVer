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
	bool canExit;
	bool needAnswer;
	 enum Command status;
	int step ;
	string tempInfo;
	CMD cmd;
	CMD cmdRecvd;
	idType userID;
	ClientType userType ;
	User* user;
	Text* input;
	Text* output;
	inline	void waitForAnswer();
	inline void sendRequest();
	static unordered_map<string, enum Command> Client_Command;
public:
	Client(Text& in,Text& out);
	~Client();
	void ClientMain();
	void whenLogIn();
	void whenLogOut();
	void whenSignIn();
	void whenInfome();
	void sendRequestWithoutAnswer();
};

