#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

extern FILE* LogFile = fopen("Log file", "a");

#define logging(func, ...) do{					             \
				           fprintf(LogFile,func, __VA_ARGS__);\
						   }while(0);


#define ERROR_OCCURRED_CALLING(func, msg) logging("%s %s at %s(%d):%s\n\n", #func, (msg), __FILE__, __LINE__, __func__)