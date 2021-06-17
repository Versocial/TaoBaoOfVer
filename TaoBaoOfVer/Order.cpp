#include "Order.h"



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
	return priceType();
}

int Order::kinds()
{
	return goodsSet.size() ;
}

void Order::addGood(idType id, Number num)
{
	if (goodsSet.count(id)) {
		goodsSet[id] = num;
	}
	else {
		goodsSet.insert(make_pair(id, num));
	}
	return;
}

string Order::toShow(GoodsControler* good)
{
	return string();
}

Object* Order::getByStream(istream&input)
{
	input >> OrderdTime>>total>>sellerID>>consumerID;
	idType id; input >> id;
	Number num;
	while (id != _INVALID_ID) {
		input >> num;
		addGood(id, num);
	}
	return nullptr;
}

string Order::turnIntoString() const
{
	string ans = to_string(OrderdTime)+" "+to_string(total)+" "+to_string(sellerID)+" "+ to_string(consumerID) +"\n";
	auto it = goodsSet.begin();
	goodsSet.begin();
	while (it != goodsSet.end()) {
		ans +=to_string( it->first);
		ans += " ";
		ans += to_string(it->second);
		ans += "\n";
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

bool Order::OrderNow(GoodsControler* good)
{
	OrderdTime = time(NULL);
	auto it = goodsSet.begin();
	total = 0;
	while (it != goodsSet.end()) {
		if (good->containsInMemory(it->first)) {
			total += ((Good*)good->getObjectInMemory(it->first))->getPrice()*it->second;
		}
		else {

			return false; 
		}
	}
	return true;
}