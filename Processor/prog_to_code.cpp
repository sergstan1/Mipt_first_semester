#include "text.h"
#include "Processor.h"


FILE* Prog_to_code(FILE* prog)
{
	FILE* fp = fopen("code.txt", "w");

	if (fp == NULL)
	{
		printf("ERROR, could not open file\n");
		return NULL;
	}
	char* text = {};

	Getfile(prog, &(text));

	char symb[] = ";";
	char** lineptr = (char**)calloc(Strcount(text, &symb[0]) + EPS, sizeof(char*));

	int nlines = Getptr_s(lineptr, text + 1);

	size_t i = 0;
	size_t j = 0;

	int end = 0;

	for (; end == 0 && i < nlines; i++)
	{
		while (isspace(lineptr[i][j]))
			j++;
		if (strcmp(&lineptr[i][j], "mul") == 0)
			fprintf(fp, "%d\n", mul);
		else if (strcmp(&lineptr[i][j], "div") == 0)
			fprintf(fp, "%d\n", divis);
		else if (strcmp(&lineptr[i][j], "add") == 0)
		{
			fprintf(fp, "%d\n", add);
		}
		else if (strcmp(&lineptr[i][j], "sub") == 0)
			fprintf(fp, "%d\n", sub);
		else if (strncmp(&lineptr[i][j], "push", strlen("push") - 1) == 0)
		{
			fprintf(fp, "%d %lf\n", push, atof(lineptr[i] + 6));
		}
		else if (strcmp(&lineptr[i][j], "pop") == 0) 
			fprintf(fp, "%d\n", pop);
		else if (strcmp(&lineptr[i][j], "in") == 0)
			fprintf(fp, "%d\n", in);
		else if (strcmp(&lineptr[i][j], "out") == 0)
			fprintf(fp, "%d\n", out);
		else if (strcmp(&lineptr[i][j], "halt") == 0)
		{
			fprintf(fp, "%d\n", halt);
			end++;
		}
		else
		{
			fprintf(fp, "Unknow command\n");
		}
	}
	fclose(fp);

	fp = fopen("code.txt", "r");

	return fp;
}

