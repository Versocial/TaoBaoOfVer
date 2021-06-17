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
protected:
	double discount;
	static bool canBeName(string name);
	virtual priceType getPrice()const;
	void  setOriginalPrice(priceType price);
	void initGood(idType id, istream& input, ostream& output);
public:
	Good();
	Good(istream&);// when client read info
	Good(idType id);
	Good(idType id, idType sellerId, string name, priceType price,Number selling);//for create a new good
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

class book :public Good{
private:
	static double BookDiscount;
public:
	virtual priceType getPrice()const;
};
class clouthing :public Good {
private:
	static double ClouthDiscount;
public:
	virtual priceType getPrice()const;
};
class electronic :public Good {
private:
	static double ElecDiscount;
public:
	virtual priceType getPrice()const;
};