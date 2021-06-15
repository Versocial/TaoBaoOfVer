#include "Client.h"

#define send(x) ;*output<<" "<<(x)<<" ";
#define recv(x) ;*input>>(x);
#define CUser ((Consumer*)User)
#define SUser ((Seller*)User)

int main() {
	
	Server* server = Server::getInstance(cin,cout);
    Client* client = new Client();
    client->ClientMain();
    delete(client);
    delete(server);

}

Client::Client(istream& in, ostream& out) {
	userType = Visitor;
	status = Exit;
	step = 1;
    input = &in;
    output = &out;
}

void Client::ClientMain()
{

    while (1) {
        recv(cmd);
        switch (cmd)
        {
        case Exit: step = 1; if (userType == HalfSeller || userType == HalfConsumer)userType = Visitor; break;
            break;
        case ShowGoods:/**/cmd = status; break;
        case LogIn:
            break;
        case LogOut:
            break;
        case SignIn:manageSignIn();
            break;
        case End:
            // server->save(); 
            return;
            break;
        default:
            break;
        }
        status = (Command)cmd;
    }
}
