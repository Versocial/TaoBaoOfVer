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
	priceType originalPrice;
	double discount;
protected:
	Good(istream&);
	static bool canBeName(string name);
	virtual priceType getPrice()const;
	void  setOriginalPrice(priceType price);
	void initGood(idType id, istream& input, ostream& output);
public:
	Good();
	Good(idType id);
	unsigned long long SoldNum()const;
	Number SellingNum()const;
	bool sell(Number selling);
	bool increaseSelling(Number num);
	bool decreaseSelling(Number num);
	bool setSelling(Number num);
	priceType getOriginalPrice()const;
	bool changeName(string name);
	idType getSellerID()const;
	bool setDiscount(double discount);

	virtual Object* getByStream(istream&);
	virtual string turnIntoString()const;
	virtual bool deleteByPtr();

	virtual string toShow()const;
};