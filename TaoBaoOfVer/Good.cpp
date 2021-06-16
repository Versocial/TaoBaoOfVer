#include "Good.h"
#include <regex>
#define EXIT_CMD_   ("@exit")
bool Good::canBeName(string name)
{
	regex rx("^[0-9a-zA-Z]+$");
	return name.length() >= 3 && name.length() <= 15 && regex_match(name, rx);
}

priceType Good::getPrice()const
{
	return originalPrice;
}

void Good::setOriginalPrice(priceType price)
{
	originalPrice = price;
}

void Good::initGood(idType id, istream& input, ostream& output)
{
	sellingNum = 0; soldNum = 0;
	output << "Your trade good "<<id<<" is initializing now !" << " And you can enter \"" << EXIT_CMD_ << "\" to exit if you want.\n";
	ID = id;
	output  << " Please enter the original price for your trade good "<< "[ " << id << " ]"<<" !\n";
	input>>originalPrice; input.clear(); input.ignore(numeric_limits<streamsize>::max(), '\n');
	output << "Your trade good [ " << id << " ] will be $" << originalPrice << " for each one.\n";
	output << "Please enter the  name for Your trade good [ " << id << " ] ";
	input>> name; input.clear(); input.ignore(numeric_limits<streamsize>::max(), '\n');
	while (!canBeName(name)) {
		if (name == EXIT_CMD_)cout << "Exit trade good initializing.\n";
		else cout << "Please type in again name of the trade good [ " << id << " ].\n";
		input>>name;; input.clear(); input.ignore(numeric_limits<streamsize>::max(), '\n');
	}output << "The trade good " << "[ " << id << " ] " << "is named as" << name<<endl;
	output << "Trade good " << "[ " << id << " ] " << "initialized.\n";
}


Good::Good(idType id):Object()
{
	initGood(id, cin, cout); discount = 1;
}

Good::Good():Object()
{
}

unsigned long long Good::SoldNum()const
{
	return soldNum;
}

Number Good::SellingNum()const
{
	return sellingNum;
}

bool Good::sell(Number selling)
{
	if (sellingNum > selling) {
		sellingNum -= selling;
		if (soldNum + sellingNum > sellingNum) { soldNum += sellingNum; }
		else soldNum = (unsigned long long) - 1;
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

idType Good::getSellerID()const
{
	return sellerID;
}

bool Good::setDiscount(double Discount) 
{
	if (Discount > 1)discount =1;
	else if (Discount <= 0)return false;
	else discount = Discount;
	return true;
}


Good::Good(istream& input):Object()
{
	input >> ID>>originalPrice >> sellerID >> sellingNum >> soldNum >> name>>discount;
}


Object* Good::getByStream(istream& input)
{
	return new Good(input);
}

string Good::turnIntoString() const
{
	return " "+to_string(ID)+" "+to_string(originalPrice)+" "+to_string(sellerID)+" "+to_string(sellingNum)+" "+to_string(soldNum)+" "+name+" "+to_string(discount)+" ";
}

bool Good::deleteByPtr()
{
	if (this != NULL) {
		delete this; return true;
	}else 	return false;
}

string Good::toShow() const
{
	string postfix = "";
	if (getPrice() < originalPrice)postfix = " Now is " + to_string(originalPrice - getPrice()) + " RMB less than the Orignal Price !";
	return "trade good [ "+to_string(ID)+" ] :"+name+" price: "+to_string(getPrice())+" selling: "+to_string(sellingNum)+" sold: "+to_string(soldNum)+postfix;
}

priceType book::getPrice() const
{
	return (priceType)ceil(getOriginalPrice()*discount*GoodDiscount);
}

priceType clouthing::getPrice() const
{
	return (priceType)ceil(getOriginalPrice() * discount * ClouthDiscount);
}

priceType electronic::getPrice() const
{
	return (priceType)ceil(getOriginalPrice() * discount * ElecDiscount);
}
