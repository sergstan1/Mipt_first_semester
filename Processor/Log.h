#ifndef LOG_H
#define LOG_H

#pragma warning(disable : 4996)

#include <stdio.h>

extern FILE* LogFile = fopen("Log_file.txt", "a");

#define logging(func, ...) do{					             \
				           fprintf(LogFile,func, __VA_ARGS__);\
						   }while(0);\


#define ERROR_OCCURRED_CALLING(func, msg) logging("%s %s at %s(%d):%s\n\n", #func, (msg), __FILE__, __LINE__, __func__)


#endif