#include "User.h"
#include <regex>
#define EXIT_CMD_   ("@exit")
#define ReadByCin(key)  ;cin>>(key);cin.clear();cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

 bool User::canBePassword(string code)
{
	regex rx("^[0-9a-zA-Z]+$");
	return code.length()>=6&&code.length()<=15&& regex_match(code, rx);
}
 
 bool User::canBeName(string name)
{
	regex rx("^[0-9a-zA-Z]+$");//not Chinese Name supported.
	return name.length() >= 2 && name.length() <= 15 && regex_match(name, rx);
}

 bool User::initUser(idType id)
 {
	 money = 0;
	 cout << "Your count " << id << " initializing now !" << " And you can enter \"" << EXIT_CMD_ << "\" to exit if you want.\n";
	 ID = id;
	 cout <<"["<<id<<"]"<< "Please enter your password, which must be : digit or label , 6 to15 characters.\n";
	 ReadByCin(password);
	 while (!canBePassword(password)) {
		 if (password == EXIT_CMD_)return  false;
		 cout << "[" << id << "]" << "Illegal password Format ! Please type in again your password, which must be : digit or label , 6 to15 characters.\n";
		 ReadByCin(password);
	 }
	 cout << "[" << id << "]" << "Your password is " << password<<endl;
	 cout << "[" << id << "]" << "Please enter your name, which must be : digit or label , 2 to15 characters.\n";
	 ReadByCin(name);
	 while (!canBeName(name)) {
		 if (name == EXIT_CMD_)return  false;
		 cout << "Illegal Name Format ! Please type in again your password, which must be : digit or label , 6 to15 characters.\n";
		 ReadByCin(name);
	 }
	 cout << "[" << id << "]" << "Your name is " << name << endl;
	 cout << "[" << name << "]" << "You have your count now ! Enjoy your time !\n";
	 return true;
 }


bool User::changeCode(string code)
{
	if (canBePassword(code)) {
		this->password = code;
		return true;
	}	else 	return false;
}

bool User::changeName(string name)
{
	if (canBeName(name)) {
		this->name = name;
		return true;
	}  else 	return false;
}

int User::income(moneyType income)
{
	if (money + income > 0) {
		money += income;
		return 1;
	}else 	return 0;
}

int User::outcome(moneyType outcome)
{
	if (money - outcome > 0) {
		money -= outcome;
		return 1;
	}
	else 	return 0;
}


moneyType User::Money()const
{
	return money;
}

string User::turnIntoString() const
{
	return " " + to_string(ID) + " " + password + " " + " " + to_string(money) + " " + name + " ";
}

User::User():Object()
{
}

User::User(string str):Object()
{
	istringstream input(str);
	input >> ID >> password >> money >> name;
}

User::User(istream& input):Object()
{
	input >> ID >> password >> money >> name;
}

User::User(const idType id, const string& code,const string& name):Object(id) {
	this->password = code;
	this->name = name;
}
