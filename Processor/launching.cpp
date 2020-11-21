#include "Processor.h"
#include "text.h"
#include "Stack.h"

#pragma warning(disable : 4996)

static struct_label* Labels = (struct_label*)calloc(STARTSIZE, sizeof(struct_label));

double Read_code(FILE* fp)
{
	char* commands = {};

	fclose(fp);

	fp = fopen("code.txt", "rb");

	int nsymb = Getfile(fp, &commands);

	fseek(fp, 0, 0);

	int file_command = 0;

	double temp1 = 0, temp2 = 0;

	int scanf_result = 0;

	Stack stk = { 0, 0, 0, 0 , 0 };
	StackCtor(&stk);

	size_t llength = STARTSIZE;

	if (Labels == NULL)
	{
		printf("No memory\n");

		exit(1);
	}

	char* rip = commands + 1;

	while (file_command != halt)
	{
		file_command = *(int*)rip;
		rip += sizeof(int);

		switch (file_command)
		{
		case mul:
			temp1 = Pop(&stk);
			temp2 = Pop(&stk);
			Push(&stk, temp1 * temp2);

			break;
		case divis:
			temp1 = Pop(&stk);
			temp2 = Pop(&stk);
			Push(&stk, temp2 / temp1);

			break;
		case add:
			temp1 = Pop(&stk);
			temp2 = Pop(&stk);
			Push(&stk, temp1 + temp2);

			break;
		case sub:
			temp1 = Pop(&stk);
			temp2 = Pop(&stk);
			Push(&stk, temp2 - temp1);

			break;
		case sqaure:
			temp1 = Pop(&stk);
			temp1 = sqrt(temp1);
			Push(&stk, temp1);

			break;

		case push:
			file_command = *(int*)rip;
			rip += sizeof(int);
			
			switch (file_command)
			{
			case number:
				temp2 = *(double*)rip;
				rip += sizeof(double);

				Push(&stk, temp2);

				break;
			case reg:
				file_command = *(int*)rip;
				rip += sizeof(int);

				switch (file_command)
				{
				case a:
					Push(&stk, ax);

					break;
				case b:
					Push(&stk, bx);

					break;
				case c:
					Push(&stk, cx);

					break;
				default:
					printf("Unknow register\n");

					exit(1);
					break;
				}
				break;
			default:
				printf("Unknow push command\n");

				exit(1);
				break;
			}
			break;
		case pop:
			file_command = *(int*)rip;
			rip += sizeof(int);

			switch (file_command)
			{
			case reg:
				file_command = *(int*)rip;
				rip += sizeof(int);

				switch (file_command)
				{
				case a:
					ax = Pop(&stk);

					break;
				case b:
					bx = Pop(&stk);

					break;
				case c:
					cx = Pop(&stk);

					break;
				default:
					printf("Uknow register\n");

					exit(1);
					break;
				}

				break;
			case number:
				Pop(&stk);

				break;
			default:
				printf("Uknow push command\n");

				exit(1);
				break;
			}
			break;
		case in:
			printf("Enter number:\n");

			scanf_result = scanf("%lf", &temp2);
			Check_scanf(scanf_result,&temp2);
			scanf_result = 0;

			Push(&stk, temp2);
			break;
		case out:
			temp1 = Pop(&stk);
			printf("%lf\n", temp1);

			break;
		case label:
			file_command = *(int*)rip;
			rip += sizeof(int);

			Labels[file_command].pos = rip;

			break;
		case jump:
			file_command = *(int*)rip;

			if (Labels[file_command].pos == NULL)
			{
				Labels[file_command].repeat_status = 1;

				rip = Transport(commands + 1);
			}
			else
			{
				rip = Labels[file_command].pos;
			}

			break;
		case jae:
			temp1 = Pop(&stk);
			temp2 = Pop(&stk);
			Push(&stk, temp2);
			Push(&stk, temp1);

			file_command = *(int*)rip;
			rip += sizeof(int);

			if (temp1 <= temp2)
			{
				if (Labels[file_command].pos == NULL)
				{
					Labels[file_command].repeat_status = 1;

					rip = Transport(commands + 1);
				}
				else
				{
					rip = Labels[file_command].pos;
				}
			}

			break;
		case ja:
			temp1 = Pop(&stk);
			temp2 = Pop(&stk);
			Push(&stk, temp2);
			Push(&stk, temp1);

			file_command = *(int*)rip;
			rip += sizeof(int);

			if (temp1 < temp2)
			{
				if (Labels[file_command].pos == NULL)
				{
					Labels[file_command].repeat_status = 1;

					rip = Transport(commands + 1);
				}
				else
				{
					rip = Labels[file_command].pos;
				}
			}

			break;
		case jbe:
			temp1 = Pop(&stk);
			temp2 = Pop(&stk);
			Push(&stk, temp2);
			Push(&stk, temp1);

			file_command = *(int*)rip;
			rip += sizeof(int);

			if (temp1 >= temp2)
			{
				if (Labels[file_command].pos == NULL)
				{
					Labels[file_command].repeat_status = 1;

					rip = Transport(commands + 1);
				}
				else
				{
					rip = Labels[file_command].pos;
				}
			}

			break;
		case jb:
			temp1 = Pop(&stk);
			temp2 = Pop(&stk);
			Push(&stk, temp2);
			Push(&stk, temp1);

			file_command = *(int*)rip;
			rip += sizeof(int);

			if (temp1 < temp2)
			{
				if (Labels[file_command].pos == NULL)
				{
					Labels[file_command].repeat_status = 1;

					rip = Transport(commands + 1);
				}
				else
				{
					rip = Labels[file_command].pos;
				}
			}

			break;
		case je:
			temp1 = Pop(&stk);
			temp2 = Pop(&stk);
			Push(&stk, temp2);
			Push(&stk, temp1);

			file_command = *(int*)rip;
			rip += sizeof(int);

			if (temp1 == temp2)
			{
				if (Labels[file_command].pos == NULL)
				{
					Labels[file_command].repeat_status = 1;

					rip = Transport(commands + 1);
				}
				else
				{
					rip = Labels[file_command].pos;
				}
			}

			break;
		case jne:
			temp1 = Pop(&stk);
			temp2 = Pop(&stk);
			Push(&stk, temp2);
			Push(&stk, temp1);

			file_command = *(int*)rip;
			rip += sizeof(int);

			if (temp1 != temp2)
			{
				if (Labels[file_command].pos == NULL)
				{
					Labels[file_command].repeat_status = 1;

					rip = Transport(commands + 1);
				}
				else
				{
					rip = Labels[file_command].pos;
				}
			}

			break;
		case halt:

			break;
		default:
			printf("Unknow command\n");

			exit(1);
			break;
		}
	}
	if ((&stk)->size > 1)
	{
		printf("Unfinished commands\n");
		return NULL;
	}
	double res = Pop(&stk);
	
	Verify_Stack(&stk);

	return res;
}


char* Transport(char* rip)
{
	int file_command = 0;

	while (file_command != halt)
	{
		file_command = *(int*)rip;
		rip += sizeof(int);

		switch (file_command)
		{
		case mul:
		case divis:
		case add:
		case sub:
		case in:
		case out:
			break;
		case push:
			file_command = *(int*)rip;
			rip += sizeof(int);

			switch (file_command)
			{
			case number:
				rip += sizeof(double);

				break;
			case reg:
				rip += sizeof(int);

				break;
			default:
				printf("Unknow push command\n");

				exit(1);
				break;
			}
			break;
		case pop:
			file_command = *(int*)rip;
			rip += sizeof(int);

			switch (file_command)
			{
			case reg:
				rip += sizeof(int);

				break;
			case number:

				break;
			default:
				printf("Uknow push command\n");

				exit(1);
				break;
			}
			break;
		case label:
			file_command = *(int*)rip;
			rip += sizeof(int);

			if (Labels[file_command].repeat_status == 1)
			{
				Labels[file_command].repeat_status = 0;

				return rip;
			}

			break;
		case jump:
		case jae:
		case jbe:
		case ja:
		case jb:
		case je:
		case jne:
			rip += sizeof(int);

			break;
		case halt:
			printf("No label\n");

			exit(1);
		default:
			printf("Unknow command\n");

			exit(1);
			break;
		}
	}
}



void Check_scanf(int result, double* a)
{
	const int number_of_inputs = 1;

	if (result != number_of_inputs)
	{
		char c = '0';
		int real_number_of_inputs = 0;
		while (real_number_of_inputs != number_of_inputs)
		{
			printf("Wrong input!\n\n");

			printf("Generate EOF:\n");

			while ((c = getchar()) != EOF)
			{
				;
			}

			printf("Enter number:\n");
			real_number_of_inputs = scanf("%lf", a);
		}
	}
}
