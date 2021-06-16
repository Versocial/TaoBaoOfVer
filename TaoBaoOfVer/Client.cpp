#include "Client.h"

#define send(x) {output.clear();output<<" "<<(x);}
#define recv(x) {input>>(x);}
#define CUser ((Consumer*)User)
#define SUser ((Seller*)User)
static 	Server*server ;

int main() {
    char S2C[60] = "0";
    char C2S[60] = "";
    Client* client = new Client(S2C, C2S);
    server = Server::getInstance(C2S,S2C);
    client->ClientMain();
    delete(client);
    delete(server);
}

Client::Client(char* in, char* out) {
	userType = Visitor;
	status = Exit;
	step = 1;
    inBuffer = in;
    outBuffer = out;
}

void Client::ClientMain()
{
    while (1) {
        if (!*inBuffer||*outBuffer) continue;
        istringstream input(inBuffer);
        ostringstream output("");
        recv(cmd);
         cout << "cli: " << cmd << endl;
        string ou="3  c 1001"; 
        //cin >> ou; 
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
        memcpy(outBuffer, output.str().c_str(), strlen(output.str().c_str()));
        *inBuffer = 0;
        status = (Command)cmd;
    }
}
