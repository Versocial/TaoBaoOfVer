#include "Object.h"
#define priceType unsigned int
#define Number unsigned int

class Good:public Object
{
private:
	string name;
	idType sellerID;
	Number sellingNum;
	unsigned long long  soldNum;
protected:

	priceType originalPrice;
	virtual priceType getPrice();
	//Good(istream&);

public:
	unsigned long long SoldNum();
	Number SellingNum();
	bool sell(Number selling);
	bool increaseSelling(Number num);
	bool decreaseSelling(Number num);
	bool setSelling(Number num);
	priceType getOriginalPrice();
	bool changeName(string name);
	idType getSeller();
	virtual Object* getByStream(istream&);
	virtual string turnIntoString()const;
	virtual bool deleteByPtr();
};