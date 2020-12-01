#include "text.h"


void Writelines(char* Lineptr[], const int numberliens, FILE* fp)
{
	int i;

	for (i = 0; i < numberliens; i++)
	{
		fputs(Lineptr[i], fp);
		if (Lineptr[i][strlen(Lineptr[i]) - 1] != ':')
			fputc(';', fp);
	}
}


int Getfile(FILE* fp, char** text)
{
	size_t nsymb = 0;

	fseek(fp, 0, 2);

	long end_file = ftell(fp);

	if (end_file == -1L)
		return (ERROR_END_OF_FILE);

	*text = (char*)calloc(end_file, sizeof(char) + EPS);

	if (text == NULL)
	{
		return STACKOVERWHELM;
	}

	**text = '\n';

	fseek(fp, 0, 0);

	if ((nsymb = fread(*text + 1, sizeof(char), end_file, fp)) <= end_file)
	{
		if (ferror(fp))
		{
			return GP_WRONGINPUT;
		}
		else
		{
			assert(text != NULL);

			*(*text + nsymb + 1) = '\n';
			*(*text + nsymb + 2) = '\0';
			return nsymb + 3;
		}
	}
	else
	{
		return STACKOVERWHELM;
	}
}


int Getptr(char* Lineptr[], char* text)
{
	int i = 0;

	char* pos = strtok(text, ")(");

	text = text + strlen(pos) + 1;

	char* temp = (char*)calloc(3 + EPS, sizeof(char));
	temp[0] = '(';
	temp[1] = '\0';

	Lineptr[i++] = temp;

	char* close = strchr(text, ')') - 1;
	char* open = strchr(text, '(') - 1;

	while (pos != NULL)
	{
		pos = strtok(text, ")(");
		if (pos == NULL)
			break;

		text = text + strlen(pos) + 1;

		if ((pos + strlen(pos) - 1) == open && open != NULL)
		{
			char* temp = (char*)calloc(3 + EPS, sizeof(char));
			if (temp == NULL)
			{
				printf("No memory\n");

				exit(1);
			}
			temp[0] = '(';
			temp[1] = '\0';

			Lineptr[i++] = pos;

			Lineptr[i++] = temp;

			open = strchr(text, '(') - 1;
		}
		else if ((pos + strlen(pos) - 1) == close && close != NULL)
		{
			char* temp = (char*)calloc(3 + EPS, sizeof(char));
			if (temp == NULL)
			{
				printf("No memory\n");

				exit(1);
			}
			temp[0] = ')';
			temp[1] = '\0';

			Lineptr[i++] = pos;

			Lineptr[i++] = temp;

			close = strchr(text, ')') - 1;
		}
	}
	return i;
}



int Strcount(char* str, char* symb)
{
	int i = 0;

	char* temp = (char*)calloc(strlen(str), sizeof(str[0]));
	if (temp == NULL)
	{
		printf("No memory\n");

		exit(1);
	}

	strcpy(temp, str);

	char* pos = strtok(temp, symb);

	while (pos != NULL)
	{
		i++;
		pos = strtok(NULL, symb);
	}
	return i;
}


char** Read(FILE* fp, int* pnlines)
{
	char* text = {};

	int nsymb = Getfile(fp, &(text));
	if (nsymb == GP_WRONGINPUT)
	{
		printf("Wrong input\n");

		exit(1);
	}
	if (nsymb == STACKOVERWHELM)
	{
		printf("NO memory\n");

		exit(1);
	}

	char symb[] = "(";
	char** lineptr = (char**)calloc(4 * Strcount(text, &symb[0]) + EPS, sizeof(char*));

	if (lineptr == NULL)
	{
		printf("NO memory\n");

		exit(1);
	}

	*pnlines = Getptr(lineptr, text);

	return lineptr;
}
