#include "Processor.h"
#include "text.h"
#include "Stack.h"

#pragma warning(disable : 4996)


double Read_code(FILE* fp)
{

	int file_command = 0;

	double temp1 = 0, temp2 = 0;

	int scanf_result = 0;

	Stack stk = { 0, 0, 0, 0 , 0 };
	StackCtor(&stk);

	int end = 0;

	while (end != EOF && file_command != halt)
	{
		end = fscanf(fp, "%d", &file_command);

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
		case push:
			fscanf(fp, "%lf", &temp2);
			Push(&stk, temp2);
			break;
		case in:
			printf("Enter number:\n");

			scanf_result = scanf("%lf", &temp2);
			Check_scanf(scanf_result,&temp2);
			scanf_result = 0;

			Push(&stk, temp2);
			file_command = OK;
			break;
		case out:
			temp1 = Pop(&stk);
			printf("%lf", temp1);
			file_command = OK;
			Push(&stk, temp1);
			break;
		case halt:
			break;
		default:
			printf("Unknow code\n");
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


void Check_scanf(int result, double* a)
{
	const int number_of_inputs = 1;

	if (result != number_of_inputs)
	{
		int real_number_of_inputs = 0;
		while (real_number_of_inputs != number_of_inputs)
		{
			getchar();
			printf("Wrong input. Enter numbers!\n");

			printf("Enter number:\n");
			real_number_of_inputs = scanf("%lf", a);
		}
	}
}
