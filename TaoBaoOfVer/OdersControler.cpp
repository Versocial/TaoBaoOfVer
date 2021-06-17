#pragma once
#include "OrdersControler.h"

OrdersControler* OrdersControler::  instance=NULL;

string OrdersControler::objPostfix()
{
	return "TBOD";
}

Object& OrdersControler::theObject()
{
	static Order _theOrder;
	return _theOrder;
}

OrdersControler::OrdersControler(string path) :Controler(path){

}

Order* OrdersControler::theOrder()
{
	return (Order*)&theObject();
}

OrdersControler::~OrdersControler()
{
	instance = NULL;
}

OrdersControler* OrdersControler::getInstance(const char* path)
{
	if (instance != NULL) {/* delete instance; */}
	instance= new OrdersControler(path);
	return instance;
}

void OrdersControler::addGood(idType seller,idType consumer, idType goodId, GoodNumber num)
{
	Order* order;
	if (containsInFile(seller)) {
		if (!containsInMemory(seller))readFromFile(seller);
		order = (Order*)getObjectInMemory(seller);
	}
	else {
		order = new Order(seller, consumer);
		order->setTheID(seller);
		addToMemory(order);
	}
	order->addGood(goodId, num);
	saveFile(seller);
}

string OrdersControler::toShow(GoodsControler* good)
{
	cout<< "All Orders:\n";
	set<idType> allID; AllIDInMemory(allID);
	for (idType id : allID) {
		cout<< "\n";
		cout<< ((Order*)getObjectInMemory(id))->toShow(good);
	}

	return "";
}
