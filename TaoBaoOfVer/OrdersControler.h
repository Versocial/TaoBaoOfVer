#pragma once

#include "Order.h"

class OrdersControler :public Controler {
private:
	//filePath
	virtual string objPostfix();
	//controling Type 
	virtual Object& theObject();// controling Type;
	//Id suggest
	OrdersControler(string path);
	static OrdersControler* instance;
public:
	~OrdersControler();
	static OrdersControler* getInstance(const char* path);
	void addGood(idType seller,idType consumer,idType goodId, Number num);//client :sellerID == Order ID ,but  not server 
	string toShow()const;
};
