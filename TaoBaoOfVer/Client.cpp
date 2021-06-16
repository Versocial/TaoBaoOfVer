#include "Client.h"

#define sendV(tag,x){output->setString(tag, to_string(x)); }
#define sendT(tag,x){output->setString(tag,x);}
#define recvV(tag) (input->getValue(tag))
#define recvT(tag) (input->getString(tag))
#define HasLogIn (userType==ConsumerUser||userType==SellerUser)

#define CUser ((Consumer*)User)
#define SUser ((Seller*)User)
#define WaitAnswerAndInput {needAnswer=true;canExit=true;}
#define WaitInput {canExit=true;}
#define ExitProcess {cmd=Exit;}
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
    cmd = Exit;
	step = 1;
    input = &in;
    output = &out;
}

void Client::ClientMain()
{
    needAnswer=false;
    canExit = false;
    while (1) {
        if (cmd==Exit) {           //get command for keyboard when no process running
                string command;  cin >> command;
                while (!Client_Command.count(command)) { cout << "Wrong Command.\n"; cin >> command; }
                cmd = Client_Command[command];
        }
         else if (canExit) {        //test if want to exit while in process
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
     if (needAnswer&&cmd!=Exit)waitForAnswer();
     else if (needAnswer && cmd == Exit) { waitForAnswer(); cmd = Exit; }
    switch (cmd)
    {
    case Exit:
        if (status == Exit) { continue; }
        status = Exit;sendV("cmd",Exit); sendRequest(); cout << "exit the process.\n";  step = 1; needAnswer = false; continue;
        break;
    case LogIn:whenLogIn(); break;
    case LogOut:whenLogOut(); break;
    case SignIn:whenSignIn(); break;
    default:
        break;
    }
    if (cmd == Exit) { step = 1; if (userType == HalfConsumer || userType == HalfSeller)userType = Visitor; }//outway:cmd=Exit 
   if(cmd!=Exit)  status = (Command)cmd;
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
            cout << "Please Logout Before you login.\n"; 
            ExitProcess;
        }
        else {
            cout << "Please enter User type, 'c' for Consumer and 's' for Seller\n";
            step++;
            WaitInput;
        }
        break;
    case 2:
            ReadByCin(temp);
            if (temp == "c")userType = HalfConsumer;
            else if (temp == "s")userType = HalfSeller;
            else {
                cout << "Please enter User type, 'c' for Consumer and 's' for Seller "<<temp<<" is invalid!\n"; 
                WaitInput;
                break;
            }
        cout << "Please enter your id\n";
        step++;
        WaitInput;
        break;
    case 3:
        ReadByCin(userID);
        sendV("cmd",LogIn); sendV("Type",userType==HalfConsumer?ConsumerUser:SellerUser); sendV("ID",userID);
        sendRequest();
        waitForAnswer();
        flag=recvV("Flag");
        if (!flag) { cout << "No such an User ID"<<userID<<".\n"; cmd = Exit; break; }
        cout << "Please enter your passWord.\n"; 
        step++; 
        WaitInput;
        break;
    default:
        ReadByCin(temp);
        sendV("cmd",LogIn); sendT("passWd",temp); 
        sendRequest();
        waitForAnswer(); 
        flag = recvV("Flag");
        if (!flag) {
            chance=recvV("Step"); 
            if (chance == 0) { cout << "Are you sure you not a robot ?????????" << endl; ExitProcess; }
            else { cout << "Wrong password! You have " << chance << "chances left.\n"; WaitInput;  };
            step++;
        }  else {
            temp=recvT("Name");
            if (userType == HalfConsumer) { user = new Consumer(userID, temp,"0"); userType = ConsumerUser; }
            else if (userType == HalfSeller) { user = new Seller(userID, temp,"0"); userType = SellerUser; }
            tempM=recvV("Money");
            user->income(tempM);
            cout<<"Login suceessful ! welcome "<<user->Name()<<" , your balance:"<<user->Money() <<" Have a good day ! "<< endl;
            ExitProcess;
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
    string temp;
    string temp2;
    switch (step)
    {
    case 1:
        if (userType == ConsumerUser || userType == SellerUser) {
            cout << "Please Logout Before you login.\n";
            ExitProcess;
        }
        else {
            cout << "Please enter User type, 'c' for Consumer and 's' for Seller\n";
            step++;
            WaitInput;
        }
        break;
    case 2:
        ReadByCin(temp);
        if (temp == "c")userType = HalfConsumer;
        else if (temp == "s")userType == HalfSeller;
        else {
            cout << "Please enter User type, 'c' for Consumer and 's' for Seller, " << temp << " is invalid!\n";
            WaitInput;
            break;
        }
        sendV("cmd", SignIn);  sendV("Type", temp == "c" ? ConsumerUser : SellerUser); sendV("ID", userID);
        sendRequest();
        waitForAnswer();
        userID = recvV("ID");
        if (userID == _INVALID_ID){
            cout << "Oh My God, sorry you are refused to join us for secret reason.\n";
            ExitProcess;
        }
        else {
            cout << "You can register as the ID " << userID << ", please give me your password !!\n";
            step++;
            WaitInput;
        }
        break;
    case 3:
        ReadByCin(temp);
        if(!User::canBePassword(temp)){
            cout << "Illegal password Format ! Please type in again your password, which must be : digit or label , 6 to15 characters.\n";
              WaitInput;
        }
        else {
            cout << "Please enter your name, which must be : digit or label , 2 to15 characters.\n";  
            tempInfo = temp;
            step++;
            WaitInput;
        }
        break;
    case 4:
        ReadByCin(temp2);
        if (!User::canBeName(temp2)) {
            cout << "Illegal Name Format ! Please type in again your Name, which must be : digit or label , 6 to15 characters.\n";
            WaitInput;
        }
        else {
            sendV("cmd", SignIn);
            sendT("Name", temp2);
            sendT("passWd", tempInfo);
            if (userType == HalfConsumer)user = new Consumer(userID, temp2,"0");
            else user = new Seller(userID, temp2,"0");
            sendRequest();
            cout << "OK! Type in 'y' to logIn now ! or other any key to refuse.\n";
            step++;
            WaitAnswerAndInput;
        }
        break;
    case 5:
        ReadByCin(temp);
        if (temp[0] == 'y' || temp[0] == 'Y') {
            sendV("Flag", true);
            if (userType == HalfConsumer)userType = ConsumerUser;
            else userType = SellerUser;
            cout << " Welcome ! " << user->Name()<<"Good morning ! " << endl;
            ExitProcess;
        }
        else {
            sendV("Flag", false);
            user->deleteByPtr();
            cout << "Well , you can type in \"@L\" to logIn now.\n";
            ExitProcess;
        }
        break;
    default:

        break;
    }
}
