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
	static int fileMod ;
	static int stdoutMod ;
	static FILE* _Log_File ;
	static time_t _Log_rawTime;
	static char _Log_TimeBuffer[50];
	virtual void getInstance() = 0;
public:
	static void setLogPath(const char* path);
	static void log_1(const char* strFormat, ...);
	static void log_2(const char* strFormat, ...);
	static void setLogMod(int fileMod_, int stdoutMod_);
	static void closeLog();
	static void logMem_2(void* mem, int len);

};


#endif // !LOGH