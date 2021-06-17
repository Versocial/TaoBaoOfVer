#include "Good.h"
#include "Object.h"
#include<set>
#include< unordered_map>
#include "GoodsControler.h"

using namespace::std;
#pragma once

class Order :public Object {
private:
	time_t OrderdTime;
	priceType total;
	idType sellerID;
	idType consumerID;
	unordered_map<idType,Number>goodsSet;
protected:
public:
	Order();
	Order(idType seller, idType consumer);
	priceType totalPrice();
	int kinds();
	void addGood(idType id, Number num);

	string toShow(GoodsControler* good);

	virtual Object* getByStream(istream&);//read from string 
	virtual string turnIntoString()const ;//wirte into string
	virtual bool deleteByPtr() ;//delete this

	bool concelOrder(GoodsControler* good);
	bool finishOrder(GoodsControler(*good));
	bool startOrder(GoodsControler* good);
	void setTheID(idType id);
	idType SellerID();
};