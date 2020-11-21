#include "text.h"
#include "Processor.h"


FILE* Prog_to_code(FILE* prog)
{
	FILE* fp = fopen("code.txt", "wb");

	if (fp == NULL)
	{
		printf("ERROR, could not open file\n");
		return NULL;
	}
	char* text = {};

	int nsymb = Getfile(prog, &(text));
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
	char** lineptr = (char**)calloc(Strcount(text, &symb[0]) + EPS, sizeof(char*));

	int nlines = Getptr_s(lineptr, text + 1);

	int i = 0;
	int j = 0;

	int end = 0;

	size_t llength = STARTSIZE;
	struct_label* Labels = (struct_label*)calloc(llength, sizeof(struct_label));
	if (Labels == 0)
	{
		printf("NO memory\n");

		exit(1);
	}

	int label_number = 0;

	char* bytes = (char*)calloc(nlines, sizeof(char) + sizeof(double));
	if (bytes == NULL)
	{
		printf("NO memory\n");
		exit(1);
	}

	char* temp = bytes;

	for (; end == 0 && i < nlines; i++, j = 0)
	{
		if (llength <= label_number + EPS)
		{
			llength *= 2;

			Labels = (struct_label*)realloc(Labels, sizeof(struct_label) * llength);
			if (Labels == NULL)
			{
				printf("No memory\n");

				exit(1);
			}
		}

		while (isspace(lineptr[i][j]))
			j++;

		if (strcmp(&lineptr[i][j], "mul") == 0)
		{
			Tp(&bytes, mul);

			continue;
		}
		else if (strcmp(&lineptr[i][j], "div") == 0)
		{
			Tp(&bytes, divis);

			continue;
		}
		else if (strcmp(&lineptr[i][j], "add") == 0)
		{
			Tp(&bytes, add);

			continue;
		}
		else if (strcmp(&lineptr[i][j], "sub") == 0)
		{
			Tp(&bytes, sub);

			continue;
		}
		else if (strncmp(&lineptr[i][j], "push", strlen("push") - 1) == 0)
		{
			Tp(&bytes, push);

			j = strlen("push") + 1;
			while (isspace(lineptr[i][j]))
				j++;

			if (isdigit(lineptr[i][j]) || lineptr[i][j] == '-')
			{
				Tp(&bytes, number);
				*(double*)bytes = atof(lineptr[i] + j);
				bytes += sizeof(double);
			}
			else
			{
				Tp(&bytes, reg);
				if (lineptr[i][j] == 'a' && lineptr[i][j + 1] == 'x')
					Tp(&bytes, a);
				else if (lineptr[i][j] == 'b' && lineptr[i][j + 1] == 'x')
					Tp(&bytes, b);
				else if (lineptr[i][j] == 'c' && lineptr[i][j + 1] == 'x')
					Tp(&bytes, c);
				else
				{
					printf("Incorrect input\n");

					exit(1);
				}
			}
			continue;
		}
		else if (strncmp(&lineptr[i][j], "pop", strlen("pop") - 1) == 0)
		{
			Tp(&bytes, pop);

			j = strlen("pop");
			while (isspace(lineptr[i][j]))
				j++;

			if (lineptr[i][j + 2] == 'a' && lineptr[i][j + 3] == 'x')
			{
				Tp(&bytes, reg);
				Tp(&bytes, a);

				continue;
			}
			else if (lineptr[i][j + 2] == 'b' && lineptr[i][j + 3] == 'x')
			{
				Tp(&bytes, reg);
				Tp(&bytes, b);

				continue;
			}
			else if (lineptr[i][j + 2] == 'c' && lineptr[i][j + 3] == 'x')
			{
				Tp(&bytes, reg);
				Tp(&bytes, c);

				continue;
			}
			else
			{
				Tp(&bytes, number);

				continue;
			}

			continue;
		}
		else if (strcmp(&lineptr[i][j], "in") == 0)
		{
			Tp(&bytes, in);

			continue;
		}
		else if (strcmp(&lineptr[i][j], "out") == 0)
		{
			Tp(&bytes, out);

			continue;
		}
		else if (strncmp(&lineptr[i][j], "jump", strlen("jump") - 1) == 0)
		{
			Tp(&bytes, jump);

			j = strlen("jump") + 1;
			while (isspace(lineptr[i][j]))
				j++;

			lineptr[i][j + strlen(&lineptr[i][j])] = '\0';

			size_t finish = 0;

			if (label_number != 0)
			{
				for (int t = 0; t < label_number; t++)
				{
					if (strcmp(&lineptr[i][j], Labels[t].name) == 0)
					{
						Tp(&bytes, t);

						finish++;

						break;
					}
				}
			}
			else if (finish == 0)
			{
				Labels[label_number] = { &lineptr[i][j], {}, 0 };

				Tp(&bytes, label_number);

				label_number++;
			}
		}
		else if ((strncmp(&lineptr[i][j], "jae", strlen("jae") - 1)) == 0)
		{
			Tp(&bytes, jae);

			j = strlen("jae") + 1;
			while (isspace(lineptr[i][j]))
				j++;

			size_t finish = 0;

			if (label_number != 0)
			{
				for (int t = 0; t < label_number; t++)
				{
					if (strcmp(&lineptr[i][j], Labels[t].name) == 0)
					{
						Tp(&bytes, t);

						finish++;

						break;
					}
				}
			}
			else if (finish == 0)
			{
				Labels[label_number] = { &lineptr[i][j], {}, 0 };

				Tp(&bytes, label_number);

				label_number++;
			}

			continue;
		}
		else if ((strncmp(&lineptr[i][j], "jbe", strlen("jbe") - 1)) == 0)
		{
			Tp(&bytes, jbe);

			j = strlen("jbe") + 1;
			while (isspace(lineptr[i][j]))
				j++;

			size_t finish = 0;

			if (label_number != 0)
			{
				for (int t = 0; t < label_number; t++)
				{
					if (strcmp(&lineptr[i][j], Labels[t].name) == 0)
					{
						Tp(&bytes, t);

						finish++;

						break;
					}
				}
			}
			else if (finish == 0)
			{
				Labels[label_number] = { &lineptr[i][j], {}, 0 };

				Tp(&bytes, label_number);

				label_number++;
			}
			
			continue;
		}
		else if (lineptr[i][j] == 'j' && lineptr[i][j + 1] == 'a')
		{
			Tp(&bytes, ja);

			j = strlen("ja") + 1;
			while (isspace(lineptr[i][j]))
				j++;

			size_t finish = 0;

			if (label_number != 0)
			{
				for (int t = 0; t < label_number; t++)
				{
					if (strcmp(&lineptr[i][j], Labels[t].name) == 0)
					{
						Tp(&bytes, t);

						finish++;

						break;
					}
				}
			}
			else if (finish == 0)
			{
				Labels[label_number] = { &lineptr[i][j], {}, 0 };

				Tp(&bytes, label_number);

				label_number++;
			}

			continue;
		}
		else if (lineptr[i][j] == 'j' && lineptr[i][j + 1] == 'b')
		{
			Tp(&bytes, jb);

			j = strlen("jb") + 1;
			while (isspace(lineptr[i][j]))
				j++;

			size_t finish = 0;

			if (label_number != 0)
			{
				for (int t = 0; t < label_number; t++)
				{
					if (strcmp(&lineptr[i][j], Labels[t].name) == 0)
					{
						Tp(&bytes, t);

						finish++;

						break;
					}
				}
			}
			else if (finish == 0)
			{
				Labels[label_number] = { &lineptr[i][j], {}, 0 };

				Tp(&bytes, label_number);

				label_number++;
			}

			continue;
		}
		else if (lineptr[i][j] == 'j' && lineptr[i][j + 1] == 'e')
		{
			Tp(&bytes, je);

			j = strlen("je") + 1;
			while (isspace(lineptr[i][j]))
				j++;

			size_t finish = 0;

			if (label_number != 0)
			{
				for (int t = 0; t < label_number; t++)
				{
					if (strcmp(&lineptr[i][j], Labels[t].name) == 0)
					{
						Tp(&bytes, t);

						finish++;

						break;
					}
				}
			}
			else if (finish == 0)
			{
				Labels[label_number] = { &lineptr[i][j], {}, 0 };

				Tp(&bytes, label_number);

				label_number++;
			}

			continue;
		}
		else if ((strncmp(&lineptr[i][j], "jne", strlen("jne") - 1)) == 0)
		{
			Tp(&bytes, jne);

			j = strlen("jne") + 1;
			while (isspace(lineptr[i][j]))
				j++;

			size_t finish = 0;

			if (label_number != 0)
			{
				for (int t = 0; t < label_number; t++)
				{
					if (strcmp(&lineptr[i][j], Labels[t].name) == 0)
					{
						Tp(&bytes, t);

						finish++;

						break;
					}
				}
			}
			else if (finish == 0)
			{
				Labels[label_number] = { &lineptr[i][j], {}, 0 };

				Tp(&bytes, label_number);

				label_number++;
			}

			continue;
		}
		else if ((lineptr[i][strlen(&lineptr[i][j])] == ':'))
		{
			Tp(&bytes, label);

			lineptr[i][strlen(lineptr[i]) - 1] = '\0';

			size_t finish = 0;

			if (label_number != 0)
			{
				for (int t = 0; t < label_number; t++)
				{
					if (strcmp(&lineptr[i][j], Labels[t].name) == 0)
					{
						Tp(&bytes, t);

						finish++;

						break;
					}
				}
			}
		    if (finish == 0)
			{
				Labels[label_number] = { &lineptr[i][j], {}, 0 };

				Tp(&bytes, label_number);

				label_number++;
			}

			continue;
		}
		else if (strcmp(&lineptr[i][j], "sqrt") == 0)
		{
			Tp(&bytes, sqaure);

			continue;
		}
		else if (strcmp(&lineptr[i][j], "halt") == 0)
		{
			Tp(&bytes, halt);
			end++;

			continue;
		}
		else
		{
			printf("Unknow command\n");

			exit(1);
		}
	}

	fwrite(temp, sizeof(char), bytes - temp, fp);

	fclose(fp);

	fp = fopen("code.txt", "rb");

	return fp;
}


void Tp(char** pbytes, int value)
{
	*(int*)(*pbytes) = value;

	*pbytes += sizeof(int);
}
