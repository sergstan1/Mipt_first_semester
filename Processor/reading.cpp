#include "text.h"


FILE* Read_commands(FILE* input)
{
	FILE* fp = fopen("programm.txt", "w+b");

	char* text = {};

	int nsymb = Getfile(input, &text);
	if (nsymb == GP_WRONGINPUT)
	{
		printf("Wrong input\n");

		exit(1);
	}
	else if (nsymb == STACKOVERWHELM)
	{
		printf("NO memory\n");

		exit(1);
	}

	char symb[] = ";";

	char** Lineptr = (char**)calloc(Strcount(text, &symb[0]) + EPS, sizeof(char*));

	int numberlines = Getptr_s(Lineptr, text);

	Writelines(Lineptr, numberlines, fp);

	return fp;
}
