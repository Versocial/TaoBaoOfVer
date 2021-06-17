#pragma once
#include "Object.h"
#include <iostream>
#define priceType unsigned int
#define GoodNumber unsigned int
enum GoodType{
		BOOK,ELEC,CLOUTH,DEFAULT
};

class Good:public Object
{
private:
	string name;
	idType sellerID;
	GoodNumber onSelling;
	GoodNumber sellingNum;
	unsigned long long  soldNum;
	priceType originalPrice;
protected:
	GoodType type = DEFAULT;
	int discount;
	void  setOriginalPrice(priceType price);
	void initGood(idType id, istream& input, ostream& output);

	Good(istream&);// when client read info
	Good(idType id);
	Good(idType id, idType sellerId, string name, priceType price, GoodNumber selling);//for create a new good
public:
	virtual priceType getPrice()const;
	static bool canBeName(string name);
	Good();
	static Good* newGood(istream&);
	static Good* newGood(GoodType good, idType id, idType sellerId, string name, priceType price, GoodNumber selling);

	string Name();
	unsigned long long SoldNum()const;
	GoodNumber SellingNum()const;
	bool sellStart(GoodNumber selling);
	bool sellConcel(GoodNumber selling);
	bool sellFinish(GoodNumber selling);
	bool increaseSelling(GoodNumber num);
	bool decreaseSelling(GoodNumber num);
	bool setSelling(GoodNumber num);
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
	book(idType id, idType sellerId, string name, priceType price, GoodNumber selling);//for create a new good
	virtual priceType getPrice()const;
};
class clouthing :public Good {
private:
	static int ClouthDiscount;
public:
	clouthing(istream&);// when client read info
	clouthing(idType id, idType sellerId, string name, priceType price, GoodNumber selling);//for create a new good
	virtual priceType getPrice()const;
};
class electronic :public Good {
private:
	static int ElecDiscount;
public:
	electronic(istream&);// when client read info
	electronic(idType id, idType sellerId, string name, priceType price, GoodNumber selling);//for create a new good
	virtual priceType getPrice()const;
};