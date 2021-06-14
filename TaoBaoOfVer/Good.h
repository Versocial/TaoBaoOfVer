#pragma once
#include "Object.h"
#include <iostream>
#define priceType unsigned int
#define Number unsigned int

class Good:public Object
{
private:
	string name;
	idType sellerID;
	Number sellingNum;
	unsigned long long  soldNum;
protected:
	static bool canBeName(string name);
	priceType originalPrice;
	virtual priceType getPrice()const;
	Good(istream&);
	void initGood(idType id, istream& input, ostream& output);
public:
	Good(idType id);
	Good();
	unsigned long long SoldNum();
	Number SellingNum();
	bool sell(Number selling);
	bool increaseSelling(Number num);
	bool decreaseSelling(Number num);
	bool setSelling(Number num);
	priceType getOriginalPrice()const;
	bool changeName(string name);
	idType getSeller()const;

	virtual Object* getByStream(istream&);
	virtual string turnIntoString()const;
	virtual bool deleteByPtr();

	virtual string toShow()const;
};