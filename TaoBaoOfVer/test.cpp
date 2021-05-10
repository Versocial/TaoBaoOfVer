//#include<stdio.h>
//class base
//{
//public:
//	void a()
//	{
//		printf("base a\n");
//		b(1);
//	};
//	virtual void b(int x)
//	{
//		printf("base b %d \n", x);
//	};
//};
//
//class ext :public base
//{
//	virtual void b(int x)
//	{
//		printf("ext b %d \n", x);
//	};
//
//};
//
//
//class extExt :public ext{
//
//};
//
//int main() {
//	extExt* b=new extExt();
//	b->a();
//}