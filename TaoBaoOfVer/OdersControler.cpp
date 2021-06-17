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

OrdersControler::~OrdersControler()
{
	instance = NULL;
}

OrdersControler* OrdersControler::getInstance(const char* path)
{
	if (instance != NULL) { delete instance; }
	instance= new OrdersControler(path);
	instance->readOutAllFromFile();
	return instance;
}

void OrdersControler::addGood(idType seller,idType consumer, idType goodId, Number num)
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

string OrdersControler::toShow()const
{
	return string();
}
