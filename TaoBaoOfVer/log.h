#ifndef LOGH
#define LOGH

#define  _CRT_SECURE_NO_WARNINGS
#include<time.h>
#include<stdio.h>
#include <stdlib.h>
#include<stdarg.h>
#include<string.h>

//log.c
class Logger {
private:
	FILE* _Log_File;
	time_t _Log_rawTime;
	char _Log_TimeBuffer[50];
public:
	Logger(const char* path);
	void log(const char* strFormat, ...);
};


#endif // !LOGH