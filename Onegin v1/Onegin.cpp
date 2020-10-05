#include "Header.h"

int main(void)
{
	printf("# Sort Eugeniy Onegin\n");
	printf("# (c) Sergey Stanko\n\n");

	printf("Enter file name:\n");

	FILE* fp;

	char filename[MAXSIZE];

	scanf("%s", filename);

	fp = fopen(filename, "r");

	int Numberlines = 0;

	if (fp == NULL)
	{
		printf("Cannot read file\n");
		return 1;
	}
	else if ((Numberlines = Readlines(Lineptr, MAXLINES, fp)) >= 0)
	{
		fclose(fp);

		if (Error_warning)
		{
			printf("Cannot compare lines in a file\n");
			return 1;
		}

		qsort(Lineptr, Numberlines, sizeof(*Lineptr), Strcmp);

		printf("The sorted poem:\n");

		Writelines(Lineptr, Numberlines);
		return 0;
	}
	else
	{
		printf("ERROR, Too many lines\n");
		return 1;
	}
}


int Readlines(char* Lineptr[], const int maxlines, FILE* fp)
{
	int len = 0;
	char line[MAXLEN];
	char* pline;

	while ((len = Getpoemline(line, MAXLEN, fp)) > 0 || len == GPO_WRONGINPUT)
	{
		if (len == GPO_WRONGINPUT)
		{
			continue;
		}
		if (Numberlines > maxlines || (pline = (char*)(malloc(sizeof(char) * MAXLEN))) == NULL)
		{
			return STACKOVERWHELM;
		}
		else
		{
			strcpy(pline, line);
			Lineptr[Numberlines++] = pline;
		}
	}
	return Numberlines;
}


int Getpoemline(char* pline, const int limit, FILE* fp)
{

	int c = '0';
	int len = 0;

	while ((c = getc(fp)) != EOF && len < limit && c != '\n')
	{
		if ((unsigned char)isalnum(c) || (unsigned char)isprint(c) || (unsigned char)isspace(c))
		{
			*pline = c;
			len++;
			pline++;
		}
		else
		{
			pline -= len;
			Number_of_errors++;
			Error_warning = true;
			return GPO_WRONGINPUT;
		}
	}

	if (c == '\n' && Number_of_errors > 0)
	{
		Numberlines++;
		printf("ERROR, Wrong input in line %d\n", Numberlines);

		Number_of_errors = 0;

		return  GPO_WRONGINPUT;
	}

	*pline = '\0';

	return len;
}


void Writelines(char *Lineptr[], int nlines)
{
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", Lineptr[i]);
}

int Strcmp(const void *s1, const void *s2)
{
	assert(s1 != NULL);
	assert(s2 != NULL);

	char* temp1 = *((char **)s1);
	char* temp2 = *((char **)s2);

	for (; *temp1 == *temp2; temp1++, temp2++)
	{
		if (*temp2 == '\0')
			return 0;
	}
	return *temp1 - *temp2;
}




