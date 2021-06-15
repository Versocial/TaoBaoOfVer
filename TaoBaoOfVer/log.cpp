#include"log.h"
#define fileOK (fileMod>0&&_Log_File!=NULL)
#define stdoutOK (stdoutMod>0 )
#define fileOK2 (fileMod>1&&_Log_File!=NULL)
#define stdoutOK2 (stdoutMod>1 )

int Logger::fileMod = 0;
int Logger::stdoutMod = 0;
FILE* Logger::_Log_File = NULL;
 time_t Logger::_Log_rawTime;
 char Logger::_Log_TimeBuffer[50];

    void Logger::setLogPath(const char* path) {
    char tempPath[100]; memcpy(tempPath, path, 100);
    memset(_Log_TimeBuffer, 0, 50);
    time(&_Log_rawTime);
    struct tm* time = localtime(&_Log_rawTime);
    strftime(_Log_TimeBuffer, sizeof(_Log_TimeBuffer), "%Y_%m_%d_%H_%M_%S", localtime(&_Log_rawTime));
    strcat(tempPath, "log_"); strcat(tempPath, _Log_TimeBuffer); strcat(tempPath, ".log");
    if (fileMod > 0) {
        _Log_File = fopen(tempPath, "a+");
        if (_Log_File == NULL) { printf("[LOG ]: Log init error.\n"); }
    }
    strftime(_Log_TimeBuffer, sizeof(_Log_TimeBuffer), "\n{LOG }: Start Time = %Y/%m/%d %H:%M:%S \n", localtime(&_Log_rawTime));
    if (fileOK) fprintf(_Log_File, _Log_TimeBuffer);
}

void Logger:: log_1(const char* strFormat, ...) {
    if (!fileOK && !stdoutOK)return;

    time(&_Log_rawTime);
    struct tm* time = localtime(&_Log_rawTime);
    strftime(_Log_TimeBuffer, sizeof(_Log_TimeBuffer), "\n[ %Y/%m/%d %H:%M:%S ]   ", time);
    if (fileOK && _Log_File == NULL) { printf("[LOG ]: NOT INIT FILE "); fileMod = 0; }
    va_list ap;
    va_start(ap, strFormat);
    if (fileOK) {
        fprintf(_Log_File, _Log_TimeBuffer);
        vfprintf(_Log_File, strFormat, ap);
        fprintf(_Log_File, "\n");
    }
    if (stdoutOK) {
        printf(_Log_TimeBuffer);
        vprintf(strFormat, ap);
        printf("\n");
    }
}

void Logger::log_2(const char* strFormat, ...) {
    if (!fileOK && !stdoutOK)return;

    time(&_Log_rawTime);
    struct tm* time = localtime(&_Log_rawTime);
    strftime(_Log_TimeBuffer, sizeof(_Log_TimeBuffer), "\n[ %Y/%m/%d %H:%M:%S ]   ", time);
    if (fileOK && _Log_File == NULL) { printf("[LOG ]: NOT INIT FILE "); fileMod = 0; }
    va_list ap;
    va_start(ap, strFormat);
    if (fileOK2) {
        fprintf(_Log_File, _Log_TimeBuffer);
        vfprintf(_Log_File, strFormat, ap);
        fprintf(_Log_File, "\n");
    }
    if (stdoutOK2) {
        printf(_Log_TimeBuffer);
        vprintf(strFormat, ap);
        printf("\n");
    }
}

void Logger::setLogMod(int fileMod_, int stdoutMod_) {
    fileMod = fileMod_;
    stdoutMod = stdoutMod_;
}

void Logger:: closeLog() {
    if (_Log_File != NULL)  free(_Log_File);
    _Log_File = NULL;
}

void Logger:: logMem_2(void* mem, int len) {
    if (!stdoutOK2 && !fileOK2)return;
    int k = 0;
    while (k < len) {
        if (stdoutOK2)printf("%02X ", ((unsigned char*)mem)[k]);
        if (fileOK2)fprintf(_Log_File, "%02X ", ((unsigned char*)mem)[k]);
        k++;
        if (k % 8 == 0) { if (stdoutOK2) printf("\n"); if (fileOK2)fprintf(_Log_File, "\n"); }
    } if (stdoutOK2) printf("\n"); if (fileOK2)fprintf(_Log_File, "\n");
}

