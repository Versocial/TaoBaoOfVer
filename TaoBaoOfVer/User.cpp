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

int User::income(unsigned int income)
{
	if (money + income > 0) {
		money += income;
		return 1;
	}else 	return 0;
}

int User::outcome(unsigned int)
{
	return 0;
}


string User::turnIntoString()const
{
	return string();
}

string User::turnFromString(string str)
{
	return string();
}
