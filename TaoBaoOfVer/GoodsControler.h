#include "Controler.h"
#include "Good.h"

class GoodsControler:public Controler
{
private:
	static GoodsControler* instanceG;
	GoodsControler(string path);
	~GoodsControler();
	virtual Object* NewObject();
public:
	GoodsControler* getInstance(string path);

};

