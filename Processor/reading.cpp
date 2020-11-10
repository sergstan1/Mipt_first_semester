#include "text.h"


FILE* Read_commands(FILE* input)
{
	FILE* fp = fopen("programm.txt", "w+b");

	char* text = {};

	Getfile(input, &text);

	char symb[] = ";";

	char** Lineptr = (char**)calloc(Strcount(text, &symb[0]) + EPS, sizeof(char*));

	int numberlines = Getptr_s(Lineptr, text);

	Writelines(Lineptr, numberlines, fp);

	return fp;
}
