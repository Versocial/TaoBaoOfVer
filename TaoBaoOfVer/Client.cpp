#include "Client.h"

#define initBuffer string Buffer("");
#define send(x) {;Buffer+=" "+=(x)+=" ";}
#define recv(x) {;*input>>(x);}
#define clearBuffer {output->str(Buffer);}
#define CUser ((Consumer*)User)
#define SUser ((Seller*)User)
static 	Server*server ;

stringstream C2S("");
stringstream S2C("0");

int main() {
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
        initBuffer;
        if (EOF == input->peek() || output->peek() != EOF) continue;
        recv(cmd);
         cout << "cli: " << cmd << endl;
        string k = "kk";
        cout << output->str() << endl;
        //*output << k;
        cout << output->str() << endl;
        //*output<<"sss";
        cout << output->str()<<endl;
        string ou; 
        cin >> ou;
        //*output << ou;
        cout << output->str() << endl;
        output->str(ou);
        Buffer += ou; Buffer += " ";
        //send(ou);
        cout << output->str() << endl;
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
        input->str("");
        clearBuffer;
    }
}
