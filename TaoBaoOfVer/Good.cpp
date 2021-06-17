#pragma once
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
	initGood(id, cin, cout); discount = 100;
}

Good::Good(idType id, idType sellerId, string Name, priceType money, Number selling):Object(id)
{
	sellerID = sellerId;
	name = Name;
	originalPrice = money;
	sellingNum = selling;
	soldNum = 0;
	discount = 100;
}

Good* Good::newGood(istream&input)
{
	int type;
	input >> type;
	GoodType goodType= (GoodType)type;
	Good* good;
	switch (goodType)
	{
	case BOOK:
		good= new book(input);
		break;
	case ELEC:
		good= new electronic(input);
		break;
	case CLOUTH:
		good= new clouthing(input);
		break;
	default:
		good= NULL;
		break;
	}
	return good;
}

Good* Good::newGood(GoodType goodType, idType id, idType sellerId, string name, priceType price, Number selling)
{
	Good* good;
	switch (goodType) {
	case BOOK:
		good = new book(id,sellerId,name,price,selling);
		break;
	case ELEC:
		good = new electronic(id, sellerId, name, price, selling);
		break;
	case CLOUTH:
		good = new clouthing(id, sellerId, name, price, selling);
		break;
	default:
		good = NULL;
		break;
	}
	return good;
}


Good::Good():Object()
{
}

string Good::Name()
{
	return name;
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
	if (Discount > 1)discount =100;
	else if (Discount <= 0)return false;
	else discount = Discount;
	return true;
}

GoodType Good::Type()
{
	return type;
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



int book:: BookDiscount=1;
 book::book(istream& input) :Good(input)// when client read info
 {
	 type = BOOK;
 }
 book::book(idType id, idType sellerId, string name, priceType price, Number selling) :Good(id, sellerId, name, price, selling)
 {
	 type = BOOK;
 }
 priceType book::getPrice() const
{
	return (priceType)ceil(getOriginalPrice()*discount*BookDiscount/10000);
}
 int clouthing::ClouthDiscount=1;


clouthing::clouthing(istream& input) :Good(input)// when client read info
{
	type = CLOUTH;
}

clouthing::clouthing(idType id, idType sellerId, string name, priceType price, Number selling):Good( id, sellerId,  name, price,selling)
{
	type = CLOUTH;
}
priceType clouthing::getPrice() const
{
	return (priceType)ceil(getOriginalPrice() * discount * ClouthDiscount/10000);
}
int electronic::ElecDiscount=1;
electronic::electronic(istream&input):Good(input)// when client read info
{
	type = ELEC;
}
electronic::electronic(idType id, idType sellerId, string name, priceType price, Number selling) :Good(id, sellerId, name, price, selling)
{
	type = ELEC;
}
priceType electronic::getPrice() const
{
	return (priceType)ceil(getOriginalPrice() * discount * ElecDiscount/10000);
}
