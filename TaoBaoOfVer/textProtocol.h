#pragma once
#include<regex>
#include <string>
#include <set>
using namespace::std;

class Text{
private:
	char* buf;
	int size;
	bool sended;
public:
	Text(char* buffer,int Size);
	bool empty();//empty means you can send another
	void clear();// after read it will be clear
	void sendInfo();//send
	bool infoReady();// before read will check if read 
	char* buffer();
	string getString(string tag);
	set<string> getStrings(string tag);
	void setString(string tag, string info);
	long long getValue(string Tag);
};