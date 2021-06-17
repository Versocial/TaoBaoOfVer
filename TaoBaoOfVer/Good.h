#pragma once
#include "Object.h"
#include <iostream>
#define priceType unsigned int
#define Number unsigned int
enum GoodType{
		BOOK,ELEC,CLOUTH,DEFAULT
};

class Good:public Object
{
private:
	string name;
	idType sellerID;
	Number sellingNum;
	unsigned long long  soldNum;
	priceType originalPrice;
protected:
	GoodType type = DEFAULT;
	int discount;
	virtual priceType getPrice()const;
	void  setOriginalPrice(priceType price);
	void initGood(idType id, istream& input, ostream& output);
public:
	static bool canBeName(string name);
	Good();
	Good(istream&);// when client read info
	Good(idType id);
	Good(idType id, idType sellerId, string name, priceType price,Number selling);//for create a new good

	static Good* newGood(istream&);
	static Good* newGood(GoodType good, idType id, idType sellerId, string name, priceType price, Number selling);

	string Name();
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
	GoodType Type();

	virtual Object* getByStream(istream&);
	virtual string turnIntoString()const;
	virtual bool deleteByPtr();

	virtual string toShow()const;
};

class book :public Good{
private:
	static int BookDiscount;
public:
	book(istream&);// when client read info
	book(idType id, idType sellerId, string name, priceType price, Number selling);//for create a new good
	virtual priceType getPrice()const;
};
class clouthing :public Good {
private:
	static int ClouthDiscount;
public:
	clouthing(istream&);// when client read info
	clouthing(idType id, idType sellerId, string name, priceType price, Number selling);//for create a new good
	virtual priceType getPrice()const;
};
class electronic :public Good {
private:
	static int ElecDiscount;
public:
	electronic(istream&);// when client read info
	electronic(idType id, idType sellerId, string name, priceType price, Number selling);//for create a new good
	virtual priceType getPrice()const;
};