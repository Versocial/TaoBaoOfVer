#include "Client.h"

#define send(x) {output->clear();*output<<" "<<(x);}
#define recv(x) {*input>>(x);}
#define CUser ((Consumer*)User)
#define SUser ((Seller*)User)
static 	Server*server ;

stringstream C2S("");
stringstream S2C("");

int main() {
    S2C.clear(); S2C << Exit;
    Client* client = new Client(S2C, C2S);
    server = Server::getInstance(C2S,S2C);
    client->ClientMain();
    delete(client);
    delete(server);
}

Client::Client(stringstream& in, stringstream& out) {
	userType = Visitor;
	status = Exit;
	step = 1;
    input = &in;
    output = &out;
}

void Client::ClientMain()
{
    while (1) {
        if (!output->rdbuf()->in_avail())output->str("");
        if (! input->rdbuf()->in_avail() ) continue;
        recv(cmd);
         cout << "cli: " << cmd << endl;
        string ou="3  c 1001"; 
        //cin >> ou; 
        send(ou);
        int k;
        char c;
        *output >> k;
        *output >> c;
        *output >> k;
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
