#pragma once
#include "Client.h"
#define chachePath ("../res/chache") 

#define sendV(tag,x){output->setString(tag, to_string(x)); }
#define sendT(tag,x){output->setString(tag,x);}
#define recvV(tag) (input->getValue(tag))
#define recvT(tag) (input->getString(tag))
#define recvTs(tag) (input->getStrings(tag))
#define HasLogIn (userType==ConsumerUser||userType==SellerUser)

#define CUser ((Consumer*)User)
#define SUser ((Seller*)User)
#define WaitAnswerAndInput {needAnswer=true;canExit=true;}
#define WaitInput {canExit=true;}//without answer waiting
#define ExitProcess {cmd=Exit;}
#define ReadByCin(x) {;cin>>(x); cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');}
static 	Server*server ;


unordered_map<string, enum Command> Client::Client_Command{
    { "@E", Exit},{"@L",LogIn},{"@O",LogOut}, {"@End",End},{"@S",SignIn},{"@M",Income} ,{"@P",AskGoodsInfo},{"@A",AddGood}
};


int main() {
    char S2C[600] = "0";
    char C2S[600] = "";
    Text StoC(S2C,600);
    Text CtoS(C2S, 600);
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
    goods = GoodsControler::getInstance(chachePath);
    clearChacheFiles(chachePath);
    tempID = 0;
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
    case Income:whenInfome(); break;
    case AskGoodsInfo:whenAskForAllGoods(); break;
    case AddGood:whenAddGood(); break;
    default:
        break;
    }
    if (cmd == Exit) { step = 1; if (userType == HalfConsumer || userType == HalfSeller)userType = Visitor; tempGood = NULL; }//outway:cmd=Exit 
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

void Client::sendRequestWithoutAnswer()
{
    output->sendInfo();
    input->clear();
}

void Client::whenAskForAllGoods()
{
    bool flag;
    int number;
    set<string >ans;
    idType goodID;
    switch (step)
    {
    case 1:
        cout << "Pulling ... ..."<<endl;
        sendV("cmd", AskGoodsInfo);
        sendRequest();
        waitForAnswer();
        // NO break here !
    case 2:
        if (step >= 2) {
            ReadByCin(tempInfo);
            if (tempInfo[0] == 'y' || tempInfo[0] == 'Y');
            else { cout << "exit.\n"; ExitProcess; break; }
        }
        else step++;
        flag = recvV("Flag");        
        goodID = recvV("ID");
        if(flag) ans = recvTs("Good");
        number = ans.size();
        if (number > 0)cout << "Got " << number << " Goods ! " << endl;
        else cout << "Sorry, sellers all put up the shutters now !"<<endl;
        for (string info:ans) {
            istringstream infor(info);
            tempGood = Good::newGood(infor);
            if (goods->containsInMemory(tempGood->id()))goods->removeFromMemory(tempGood->id());
            goods->addToMemory(tempGood);
            goods->saveFile(tempGood->id());
            cout << tempGood->turnIntoString()<<endl;//..
        }
        if (goodID==_INVALID_ID) { cout << "No more goods selling.\n"; ExitProcess; }
        else { 
            cout << "If you want more goods to show, type in 'y'" << endl; 
            sendV("cmd", AskGoodsInfo);
            sendV("ID", goodID);
            WaitAnswerAndInput;
        }
        break;
   default:
        break;
    }
}

void Client::whenAddGood()//////
{
    string info;
    switch (step) {
    case 1:
        if (userType != SellerUser) { cout << "No, you are not a seller !"; ExitProcess; }
        else {
            sendV("cmd", AddGood);
            sendRequest();
            cout << "Please enter its type 'b' for book ,'c' for clouth while 'e' for electronic.\n"; 
            step++;
            WaitAnswerAndInput;
        }
        break;
    case 2:
        tempID = recvV("ID");
        if (tempID == _INVALID_ID) { cout << "you are refused for unkown reason.\n"; ExitProcess; break; }
        ReadByCin(info);
        if (info == "c" || info == "b" || info == "e") {
            tempInfo= " ";
            cout << "Give its price\n";
            step++;
            switch (info[0]) {
            case 'c':ClientTempFlag = CLOUTH;
                break;
            case 'b':ClientTempFlag = BOOK;
                break;
            case 'e':ClientTempFlag = ELEC;
                break;
            }
        }
        else {
            cout << "Please enter its type 'b' for book ,'c' for clouth while 'e' for electronic , and "+info+" is invalid.\n";
        }
        WaitInput;
        break;
    case 3:
        ReadByCin(info);
        if (atoll(info.c_str()) <= 0) { cout << "Please type a reasonable price.\n"; }
        else {
            tempInfo = tempInfo + " "+info+" "+to_string(userID)+" ";
            cout << "Give its selling num\n";
            step++;
        }
        WaitInput;
        break;
    case 4:
        ReadByCin(info);
        if (atoll(info.c_str()) <= 0) { cout << "Please type a reasonable number.\n"; }
        else {
            tempInfo = tempInfo + " " + info+" 0 ";
            cout << "Give its name\n";
            step++;
        }
        WaitInput;
        break;
    case 5://type>> ID>>originalPrice >> sellerID >> sellingNum >> soldNum >> name>>discount
        ReadByCin(info);
        if (Good::canBeName(info)) {
            istringstream inputstring(to_string(ClientTempFlag)+" "+to_string(tempID)+" "+tempInfo + " " + info + " 1 ");
            Good* good = Good::newGood(inputstring);
            sendV("cmd", AddGood);
            sendV("ID", good->id());
            sendT("Name", good->Name());
            sendV("Sell", good->SellingNum());
            sendV("Price", good->getOriginalPrice());
            sendV("Type", good->Type());
            cout << "OK.\n";
            sendRequest();
            goods->addToMemory(good);
            goods->saveFile(good->id());
            ExitProcess;
        }
        else { cout << "Wrong Format !!\n"; WaitInput; }
        break;
    default:
        break;
    }
}
/*
* 
@L
s
10001
stupid

@A
b
200
100
LRF


*/
void Client::whenLogOut()
{
    switch (step) {
    case 1:
        if (!HasLogIn){
            cout << "NO, you must log in before you log out.\n";
            ExitProcess;
    }
        cout << "Oh, " << user->Name() << " , are you sure to log out ? type in 'O' or 'o' to confirm.\n" << endl;
        step++;
        WaitInput;
        break;
    case 2:
        ReadByCin(tempInfo);
        if (tempInfo[0] == 'O' || tempInfo[0] == 'o') {
            sendV("cmd", LogOut);
            sendRequestWithoutAnswer();
            user->deleteByPtr();
            user = NULL;
            userID = 0;
            userType = Visitor;
            cout << " OK .\n";
        }
        else cout << "Oh you don't really want to log out now, right?\n";
        ExitProcess;
        break;
    }
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

void Client::clearChacheFiles(const char* ChachePath)const
{   
    intptr_t hFile = 0;//文件句柄  
    struct _finddata_t fileinfo;//文件信息  
    string p(ChachePath);
    if ((hFile = _findfirst(p.assign(ChachePath).append("\\*.TBgood").c_str(), &fileinfo)) != -1)
    {
        do
        {
            string path(ChachePath);
            p  =path+ "\\" + fileinfo.name;
            remove(p.c_str());
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
        return;
}

void Client::whenInfome()
{
    moneyType money;
    bool flag=false;
    switch(step) {
    case 1:
        if (!HasLogIn) { cout << "Please log in or sign in first.\n"; ExitProcess; }
        else {
            cout << "Please enter how mang dollors you want to charge.\n";
            WaitInput;
            step++;
        }
        break;
    case 2:
        ReadByCin(money);
        sendV("cmd", Income);
        sendV("Money", money);
        sendRequest();
        waitForAnswer();
        flag = recvV("Flag");
        if (flag) { cout << "got your " << money << " dollors, Suceess ! "; user->income(money); }
        else cout << "Sorry you are refused.\n";
        ExitProcess;
        break;
    default:
        break;
    }
}
