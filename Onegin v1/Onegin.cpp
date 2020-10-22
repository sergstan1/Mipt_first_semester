#include "Header.h"

int main(void)
{
	setlocale(LC_ALL, "Rus");

	printf("# Sort Eugeniy Onegin\n");
	printf("# (c) Sergey Stanko\n\n");

	printf("Enter file name:\n");

	char filename[MAXSIZE] = {};

	scanf("%s", filename);

	FILE* fp = fopen(filename, "r+b");

	if (fp == NULL)
	{
		printf("ERROR: Cannot read file\n");
		return 1;
	}
	else
	{
		char* text = {};

		int nsymb = Getpoem(fp, &text);

		if (nsymb == GP_WRONGINPUT)
		{
			printf("ERROR: Programm couldn't read file");

			return 1;
		}

		else if (nsymb == STACKOVERWHELM)
		{
			printf("ERROR: Too many symbols");

			return 1;
		}

		else if (nsymb == ERROR_END_OF_FILE)
		{
			printf("ERROR: Couldn't count bytes to end of a file\n");

			return -1;
		}

		else
		{
			char symb[] = "\n";
			int nlines2 = Strcount(text, &symb[0], nsymb);

			char** Lineptr_original = (char**)calloc(nlines2, sizeof(char*));
			char** Lineptr_reverse = (char**)calloc(nlines2, sizeof(char*));
			char** Lineptr = (char**)calloc(nlines2, sizeof(char*));


			if (Lineptr_original == NULL || Lineptr_reverse == NULL || Lineptr == NULL)
			{
				printf("ERROR: Could not allocate memory to Lineptr\n");

				return 1;
			}

			int i = 0;
			int nlines = Getptr(Lineptr_original, text);

			for (; i < nlines; i++)
			{
				Lineptr[i] = Lineptr_original[i];
				Lineptr_reverse[i] = Lineptr_original[i];
			}

			qsort(Lineptr, nlines, sizeof(char*), Strcmp);
			qsort(Lineptr_reverse, nlines, sizeof(char*), Strcmp_reverse);

			fclose(fp);
			fp = fopen(filename, "w");

			fprintf(fp, "Sorted poem:\n");
			Writelines(Lineptr, nlines, fp);

			fprintf(fp, "\n\nSorted from back poem:\n");
			Writelines(Lineptr_reverse, nlines, fp);

			fprintf(fp, "\n\nOriginal poem:\n");
			Writelines(Lineptr_original, nlines, fp);

			printf("\nSuccess");
			fclose(fp);

			return 0;
		}
	}
}


int Strcmp(const void* s1, const void* s2)
{
	assert(s1 != NULL);
	assert(s2 != NULL);

	char* temp1 = *((char**)s1);
	char* temp2 = *((char**)s2);

	for (; *temp1 == *temp2 || isspace(*temp1) || isspace(*temp2); temp1++, temp2++)
	{
		while (isspace(*temp1))
			temp1++;
		while (isspace(*temp2))
			temp2++;
		if (*temp1 == '\0' && *temp2 == '\0')
		{
			return 0;
		}
	}
	return (*temp1 - *temp2);
}

void Writelines(char* Lineptr[], const int numberliens, FILE* fp)
{
	int i;

	for (i = 0; i < numberliens; i++)
	{
		fputs(Lineptr[i], fp);
	}
}


int Getpoem(FILE* fp, char** text)
{
	size_t nsymb = 0;

	fseek(fp, 0, 2);

	long end_file = ftell(fp);

	if (end_file == -1L)
		return (ERROR_END_OF_FILE);

	*text = (char*)calloc(end_file, sizeof(char));

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

			*(*text + nsymb + 1) = '\0';
			return nsymb + 1;
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
	char* pos = strtok(text, "\r");

	while (pos != NULL)
	{
		Lineptr[i++] = pos;
		pos = strtok(NULL, "\r");
	}
	return i;
}


int Strcmp_reverse(const void* s1, const void* s2)
{
	assert(s1 != NULL);
	assert(s2 != NULL);

	char* p1 = *(char**)s1;
	char* p2 = *(char**)s2;

	char* temp1 = (p1 + strlen(p1) - 1);
	char* temp2 = (p2 + strlen(p2) - 1);

	for (; *temp1 == *temp2 || isspace(*temp1) || isspace(*temp2); temp1--, temp2--)
	{
		while (isspace(*temp1))
			temp1--;
		while (isspace(*temp2))
			temp2--;
		if (temp1 == p1 && temp2 == p2)
		{
			return 0;
		}
	}
	return (*temp1 - *temp2);
}

bool Test_function(const char* name, int expression)
{
	if (expression)
	{
		return true;
	}
	else
	{
		printf("test %s failed\n", name);
		return false;
	}
}

void TestComparators(void)
{
	int number_tests_passed = 0, number_tests_failed = 0;

#define TEST(name, expression) ((Test_function(name, expression)) ? ++number_tests_passed : ++number_tests_failed)

	TEST("Singular letters, 'a' and 'b', regular",
		Strcmp("a", "b") > 0);
	TEST("Singular letters, 'a' and 'b', reverse",
		Strcmp_reverse("a", "b") > 0);
	TEST("'abc', 'cba', regular",
		Strcmp("abc", "cba") > 0);
	TEST("'abc', 'cba', reverse",
		Strcmp_reverse("abc", "cba") < 0);
	TEST("Equal lines, 'abcd', 'abcd', regular",
		Strcmp("abcd", "abcd") == 0);
	TEST("Equal lines, 'abcd', 'abcd', reverse",
		Strcmp_reverse("abcd", "abcd") == 0);

#undef TEST

	if (number_tests_failed != 0)
		printf("Some units tests have failed! Number of failed tests is %d\n", number_tests_failed);
}


int Strcount(char* str, char* symb, const int nsymb)
{
	int i = 0;

	char* temp = (char*)calloc(nsymb, sizeof(str[0]));

	strcpy(temp, str);

	char* pos = strtok(temp, symb);

	while (pos != NULL)
	{
		i++;
		pos = strtok(NULL, symb);
	}
	return i;

}
