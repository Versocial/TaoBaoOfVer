#pragma once
#include "User.h"
#include "UsersControler.h"
#include "Good.h"
#include "GoodsControler.h"
#include "Command.h"
#include "Server.h"
#include "sstream"
using namespace::std;

class Client
{
private:
	 enum Command status;
	int step ;
	CMD cmd;
	idType userID;
	ClientType userType ;
	User* user;
	istream* input;
	ostream* output;
public:
	Client(istream &in,ostream& out);
	void ClientMain();


};

