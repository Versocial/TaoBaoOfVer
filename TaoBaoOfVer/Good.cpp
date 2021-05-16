#include "Good.h"
#include <regex>
#define EXIT_CMD_   ("@exit")
#define ReadByInput(key)  ;input>>(key);input.clear();input.ignore(numeric_limits<streamsize>::max(), '\n'); 

bool Good::canBeName(string name)
{
	regex rx("^[0-9a-zA-Z]+$");
	return name.length() >= 3 && name.length() <= 15 && regex_match(name, rx);
}

priceType Good::getPrice()const
{
	return originalPrice;
}

void Good::initGood(idType id, istream& input, ostream& output)
{
	sellingNum = 0; soldNum = 0;
	output << "Your trade good "<<id<<" is initializing now !" << " And you can enter \"" << EXIT_CMD_ << "\" to exit if you want.\n";
	ID = id;
	output  << " Please enter the original price for your trade good "<< "[ " << id << " ]"<<" !\n";
	ReadByInput(originalPrice);
	output << "Your trade good [ " << id << " ] will be $" << originalPrice << " for each one.\n";
	output << "Please enter the  name for Your trade good [ " << id << " ] ";
	ReadByInput(name);
	while (!canBeName(name)) {
		if (name == EXIT_CMD_)cout << "Exit trade good initializing.\n";
		else cout << "Please type in again name of the trade good [ " << id << " ].\n";
		ReadByInput(name);
	}output << "The trade good " << "[ " << id << " ] " << "is named as" << name<<endl;
	output << "Trade good " << "[ " << id << " ] " << "initialized.\n";
}


Good::Good(idType id):Object()
{
	initGood(id,cin,cout);
}

Good::Good():Object()
{
}

unsigned long long Good::SoldNum()
{
	return soldNum;
}

Number Good::SellingNum()
{
	return sellingNum;
}

bool Good::sell(Number selling)
{
	if (sellingNum > selling) {
		sellingNum -= selling;
		if (soldNum + sellingNum > sellingNum) { soldNum += sellingNum; }
		soldNum = (unsigned long long) - 1;
		return true;
	}
	return false;
}

bool Good::increaseSelling(Number num)
{
	if (num + sellingNum > num) { sellingNum += num; return true; }
	else return false;
}

bool Good::decreaseSelling(Number num)
{
	if (num < sellingNum) { sellingNum -= num; return true; }
	return false;
}

bool Good::setSelling(Number num)
{
	sellingNum = num;
	return true;
}


priceType Good::getOriginalPrice()const
{
	return originalPrice;
}

bool Good::changeName(string name)
{
	this->name = name;
	return true;
}

idType Good::getSeller()const
{
	return sellerID;
}


Good::Good(istream& input):Object()
{
	input >> ID>>originalPrice >> sellerID >> sellingNum >> soldNum >> name;
}


Object* Good::getByPtr(Object* obj)
{
	return new Good(*(Good*)obj);
}

Object* Good::getByStream(istream& input)
{
	return new Good(input);
}

string Good::turnIntoString() const
{
	return " "+to_string(ID)+" "+to_string(originalPrice)+" "+to_string(sellerID)+" "+to_string(sellingNum)+" "+to_string(soldNum)+" "+name+" ";
}

bool Good::deleteByPtr()
{
	delete this;
	return false;
}

string Good::toShow() const
{
	return "trade good [ "+to_string(ID)+" ] :"+name+" price: "+to_string(getPrice())+" selling: "+to_string(sellingNum)+" sold: "+to_string(soldNum);
}
