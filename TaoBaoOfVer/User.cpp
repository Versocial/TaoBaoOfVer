#include "User.h"
#include <regex>
#define EXIT_CMD_   ("@exit")

bool User::matchWithPassWord(string passwd)const
{
	return password==passwd;
}

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

 bool User::initUser(idType id,istream& input, ostream& output)
 {
	 money = 0;
	 output << "Your count " << id << " initializing now !" << " And you can enter \"" << EXIT_CMD_ << "\" to exit if you want.\n";
	 ID = id;
	 output <<"["<<id<<"]"<< "Please enter your password, which must be : digit or label , 6 to15 characters.\n";
	 input>>(password);  input.clear(); input.ignore(numeric_limits<streamsize>::max(), '\n');
	 while (!canBePassword(password)) {
		 if (password == EXIT_CMD_) {cout << "Exit count initializing.\n"; return  false; }
		 output << "[" << id << "]" << "Illegal password Format ! Please type in again your password, which must be : digit or label , 6 to15 characters.\n";
		 input>>(password); input.clear(); input.ignore(numeric_limits<streamsize>::max(), '\n');
	 }
	 output << "[" << id << "]" << "Your password is " << password<<endl;
	 output << "[" << id << "]" << "Please enter your name, which must be : digit or label , 2 to15 characters.\n";
	 input>>(name); input.clear(); input.ignore(numeric_limits<streamsize>::max(), '\n');
	 while (!canBeName(name)) {
		 if (name == EXIT_CMD_) {cout << "Exit count initializing.\n"; return  false; }
		 output << "Illegal Name Format ! Please type in again your password, which must be : digit or label , 6 to15 characters.\n";
		 input>>(name); input.clear(); input.ignore(numeric_limits<streamsize>::max(), '\n');
	 }
	 output << "[" << id << "]" << "Your name is " << name << endl;
	 output << "[" << name << "]" << "You have your count now ! Enjoy your time !\n";
	 return true;
 }


bool User::changePassWord(string code)
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

string User::Name()const
{
	return name;
}

string User::turnIntoString() const
{
	return " " + to_string(ID) + " " + password + " " + " " + to_string(money) + " " + name + " ";
}

User::User():Object()
{
}


User::User(istream& input):Object()
{
	input >> ID >> password >> money >> name;
}
