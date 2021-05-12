#include "Good.h"

priceType Good::getPrice()
{
	return originalPrice;
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


priceType Good::getOriginalPrice()
{
	return originalPrice;
}

bool Good::changeName(string name)
{
	this->name = name;
	return true;
}

idType Good::getSeller()
{
	return sellerID;
}

Object* Good::getByStream(istream& input)
{
	return new Good(input);
}

string Good::turnIntoString() const
{
	return " "+to_string(ID)+" "+to_string(sellerID)+" "+to_string(sellingNum)+" "+to_string(soldNum)+" "+name+" ";
}

bool Good::deleteByPtr()
{
	delete this;
	return false;
}
