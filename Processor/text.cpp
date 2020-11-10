#include "text.h"


void Writelines(char* Lineptr[], const int numberliens, FILE* fp)
{
	int i;

	for (i = 0; i < numberliens; i++)
	{
		fputs(Lineptr[i], fp);
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

			*(*text + nsymb) = '\0';
			return nsymb + 1;
		}
	}
	else
	{
		return STACKOVERWHELM;
	}
}


int Getptr_s(char* Lineptr[], char* text)
{
	int i = 0;
	char* temp = text;
	char* n = temp;
	char* pos = strtok(text, ";");

	text = text + strlen(pos) + 1;

	while (pos != NULL && n != NULL)
	{
		Lineptr[i] = pos;
		n = strchr(text, '\n');
		if (n == NULL)
		{
			i++;
			pos = strtok(text, ";");
			if (pos != NULL)
			{
				Lineptr[i] = pos;
			}
			break;
		}
		text = text + strlen(text) - strlen(n);
		while (*(text + 1) == '\n')
			text++;
		pos  = strtok(text, ";");
		text = text + strlen(pos) + 1;
		i++;
	}
	return i;
}


int Strcount(char* str, char* symb)
{
	int i = 0;

	char* temp = (char*)calloc(strlen(str), sizeof(str[0]));

	strcpy(temp, str);

	char* pos = strtok(temp, symb);

	while (pos != NULL)
	{
		i++;
		pos = strtok(NULL, symb);
	}
	return i;
}


int Getptr(char* Lineptr[], char* text)
{
	int i = 0;
	char* pos = strtok(text, ";");

	while (pos != NULL)
	{
		Lineptr[i] = pos;
		pos = strtok(NULL, ";");
		i++;
	}
	return i;
}
