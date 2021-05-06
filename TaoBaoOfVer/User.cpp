#include "User.h"
#include <regex>


 bool User::canBeCode(string code)
{
	regex rx("^[0-9a-zA-Z]+$");
	return code.length()>=6&&code.length()<=15&& regex_match(code, rx);
}

 bool User::canBeName(string name)
{
	regex rx("^[0-9a-zA-Z]+$");//not Chinese Name supported.
	return name.length() >= 2 && name.length() <= 15 && regex_match(name, rx);
}


bool User::changeCode(string code)
{
	if (canBeCode(code)) {
		this->code = code;
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


string User::turnIntoString()const
{
	return " "+to_string(ID)+ " " +code + " " +" "+to_string(money)+" "+ name+" ";
	
}

moneyType User::Money()const
{
	return money;
}

idType User::id()const
{
	return id;
}

bool User::turnFromString(string str)
{
	istringstream input(str);
	input >> ID >> code >> money >> name;
	return true;
}

bool User::turnFromStream(istream& input)
{
	input >> ID >> code >> money >> name;
	return false;
}
