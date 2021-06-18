#include "Order.h"



void Order::setTheID(idType id)
{
	setID(id);
}

idType Order::SellerID()
{
	return sellerID;
}

Order::Order():Object()
{
}

Order::Order(idType seller, idType consumer)
{
	OrderdTime = 0;
	total = 0;
	sellerID = seller;
	consumerID = consumer;
}

priceType Order::totalPrice()
{
	return total;
}

int Order::kinds()
{
	return goodsSet.size() ;
}

void Order::addGood(idType id, GoodNumber num)
{
	if (goodsSet.count(id)) {
		goodsSet[id] = num;
	}
	else {
		goodsSet.insert(make_pair(id, num));
	}
	return;
}

string Order::toShow(GoodsControler* goods)
{
	priceType price = 0; auto it = goodsSet.begin();
	string ans;
	while (it != goodsSet.end()) {
		ans += "Order ID : " + to_string(id()) + " : ";
		if (goods->containsInMemory(it->first)) {
			Good* good =( (Good*)(goods->getObjectInMemory(it->first)));
			price += good->getPrice() * it->second;
			ans = ans + " seller: "+to_string(sellerID)+" price: "+to_string(good->getPrice() * it->second)+" for "+to_string(it->second)+" of such thing:" + good->toShow();
			if (OrderdTime != 0)ans =ans+ " time when " + to_string(OrderdTime) + " sold.\n";
		}
		else ans =ans+" you want "+to_string(it->second)+", but information not found in chache.";
			ans += "\n";
			it++;
	}
	return ans;
}

Object* Order::getByStream(istream&input)
{
	Order* order = new Order();
	input >>order->ID>> order->OrderdTime>>order->total>>order->sellerID>>order->consumerID;
	idType id; input >> id;
	GoodNumber num;
	while (id != _INVALID_ID) {
		input >> num;
		order->addGood(id, num);
		input >> id;
	}
	return order;
}

string Order::turnIntoString() const
{
	string ans =to_string(ID)+" "+ to_string(OrderdTime)+" "+to_string(total)+" "+to_string(sellerID)+" "+ to_string(consumerID) +" ";
	auto it = goodsSet.begin();
	while (it != goodsSet.end()) {
		ans +=to_string( it->first);
		ans += " ";
		ans += to_string(it->second);
		ans += "  ";
		it++;
	}
	ans += " 0";
		return ans;
}

bool Order::deleteByPtr()
{
	delete this;
	return false;
}

bool Order::concelOrder(GoodsControler* good)
{
	auto it = goodsSet.begin();
	while (it != goodsSet.end()) {
		if (good->containsInMemory(it->first)) {
			((Good*)good->getObjectInMemory(it->first))->sellConcel(it->second);
		}
		else {
			return false;
		}
	}
	return true;
}

bool Order::finishOrder(GoodsControler(*good))
{
	auto it = goodsSet.begin();
	while (it != goodsSet.end()) {
		if (good->containsInMemory(it->first)) {
			((Good*)good->getObjectInMemory(it->first))->sellFinish(it->second);
		}
		else {
			return false;
		}
		it++;
	}
	return true;
}

bool Order::startOrder(GoodsControler* good)
{
	OrderdTime = time(NULL);
	auto it = goodsSet.begin();
	total = 0;
	while (it != goodsSet.end()) {
		if (good->containsInMemory(it->first)) {
			total += ((Good*)good->getObjectInMemory(it->first))->getPrice()*it->second;
			if(!((Good*)good->getObjectInMemory(it->first))->sellStart(it->second))return false;
		}
		else {
			return false; 
		}
		it++;
	}
	return true;
}