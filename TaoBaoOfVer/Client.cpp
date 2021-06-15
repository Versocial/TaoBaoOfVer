#include "Client.h"


#define send(x) {;*output<<" "<<(x)<<" ";}
#define recv(x) {;*input>>(x);}
#define CUser ((Consumer*)User)
#define SUser ((Seller*)User)
static 	Server*server ;


stringstream  S2C("");
stringstream C2S("");

int main() {
    Client* client = new Client(S2C, C2S);
        server = Server::getInstance(C2S,S2C);
   // new thread(&tempWakeUp);
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
        if (input->peek() != EOF) {
            recv(cmd);
            cout << "cli: " << cmd << endl;
        }
        string ou; 
        cin >> ou; 
        send(ou);
        //switch (cmd)
        //{
        //case Exit: step = 1; if (userType == HalfSeller || userType == HalfConsumer)userType = Visitor; break;
        //    break;
        //case ShowGoods:/**/cmd = status; break;
        //case LogIn:
        //    break;
        //case LogOut:
        //    break;
        //case SignIn:manageSignIn();
        //    break;
        //case End:
        //    // server->save(); 
        //    return;
        //    break;
        //default:
        //    break;
        //}
        status = (Command)cmd;
    }
}
