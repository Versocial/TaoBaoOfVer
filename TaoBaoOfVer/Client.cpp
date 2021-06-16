#include "Client.h"

#define sendV(tag,x){output->setString(tag, to_string(x)); }
#define sendT(tag,x){output->setString(tag,x);}
#define recvV(tag) (input->getValue(tag))
#define recvT(tag) (input->getString(tag))
#define CUser ((Consumer*)User)
#define SUser ((Seller*)User)
#define WaitAnswer {needAnswer=true;canExit=true;}
#define WaitAnswerWithoutExit {needAnswer=true;}
#define ReadByCin(x) {;cin>>(x); cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');}
static 	Server*server ;


unordered_map<string, enum Command> Client::Client_Command{
    { "@E", Exit},{"@L",LogIn},{"@O",LogOut}, {"@End",End},{"@S",SignIn}
};


int main() {
    char S2C[60] = "0";
    char C2S[60] = "";
    Text StoC(S2C,60);
    Text CtoS(C2S, 60);
    Client* client = new Client(StoC, CtoS);
    server = Server::getInstance(CtoS,StoC);
    client->ClientMain();
    delete(client);
    delete(server);
}

Client::Client(Text& in, Text& out) {
	userType = Visitor;
	status = Exit;
	step = 1;
    input = &in;
    output = &out;
}

void Client::ClientMain()
{
    needAnswer=false;
    canExit = false;
    while (1) {
         //when input from cin
        if (!needAnswer) {           
                string command;  cin >> command;
                while (!Client_Command.count(command)) { cout << "Wrong Command.\n"; cin >> command; }
                cmd = Client_Command[command];
        }
        else if (canExit) {
            char First = ' ';
            while (isspace(First)) { First = getchar(); }
            if (First == '@') {
                cmd = Exit;
            }else {
                ungetc(First, stdin);
            }
            canExit = false;
        }
        //....
     if (needAnswer)waitForAnswer();
    switch (cmd)
    {
    case Exit:
        if (status == Exit) { continue; }status = Exit;
        cout << "exit the process.\n"; sendV("cmd",Exit); sendRequest(); step = 1; needAnswer = false; continue;
        break;
    case LogIn:whenLogIn(); break;
    case LogOut:whenLogOut(); break;
    case SignIn:whenSignIn(); break;
    default:
        break;
    }
    if (cmd == Exit) { step = 1; if (userType == HalfConsumer || userType == HalfSeller)userType = Visitor; }//outway:cmd=Exit 
    status = (Command)cmd;
    }
}

void Client::waitForAnswer()
{
    while (!input->infoReady()||!output->empty()) ;
    cmdRecvd=recvV("cmd");
    cout << "client recv : " << input->buffer() << endl;
    needAnswer = false;
}

void Client::whenLogIn()
{
    bool flag = false;
    string temp="";
    moneyType tempM;
    int chance = 0;
    switch (step)
    {
    case 1:
        if (userType == ConsumerUser || userType == SellerUser) {
            cout << "Please Logout Before you login.\n"; cmd = Exit;
            return;
        }
        do {
            cout << "Please enter User type, 'c' for Consumer and 's' for Seller\n";
            ReadByCin(temp);
            if (temp == "c")userType = HalfConsumer;
            if (temp == "s")userType == HalfSeller;
        } while (temp != "c" && temp != "s");
        cout << "Please enter your id\n";
        ReadByCin(userID);
        sendV("cmd",LogIn); sendV("Type",temp=="c"?ConsumerUser:SellerUser); sendV("ID",userID);
        sendRequest();
        step++;
        break;
    case 2:
        flag=recvV("Flag");
        if (!flag) { cout << "No such an User ID"<<userID<<".\n"; cmd = Exit; break; }
        cout << "Please enter your passWord.\n"; 
        step++; WaitAnswer;
        break;
    default:
        ReadByCin(temp);
        sendV("cmd",LogIn); sendT("passWd",temp); sendRequest();
        waitForAnswer(); 
        flag = recvV("Flag");
        if (!flag) {
            chance=recvV("Step"); 
            if (chance == 0){ cmd = Exit; cout << "Are you sure you not a robot ?????????"<<endl; }
            else { cout << "Wrong password! You have " << chance << "chances left.\n"; WaitAnswer;    };
            step++;
        }  else {
            temp=recvT("Name");
            if (userType == HalfConsumer) { user = new Consumer(userID, temp); userType = ConsumerUser; }
            else if (userType == HalfSeller) { user = new Seller(userID, temp); userType = SellerUser; }
            tempM=recvV("Money");
            user->changeName(temp);
            user->income(tempM);
            cout<<"Login suceessful ! welcome "<<user->Name()<<" balance:"<<user->Money() << endl;
            cmd = Exit;
        }
        break;
    }

}

void Client::sendRequest()
{
    output->sendInfo();
    input->clear();
    needAnswer = true;
}

void Client::whenLogOut()
{
}

Client::~Client()
{
    delete input;
    delete output;
}

void Client::whenSignIn()
{
}
