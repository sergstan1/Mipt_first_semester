#include "text.h"
#include "Processor.h"


int main(int argc,char** argv)
{

	printf("# Processor\n");
	printf("# (c) Sergey Stanko\n\n");


	if (argc == 1)
	{
		printf("No command line arguments\n");
		return 1;
	}
	else
	{
		FILE* fp = fopen(argv[1], "r");

		if (fp == NULL)
		{
			printf("Could not open file\n");

			return 1;
		}

		FILE* prog = Read_commands(fp);

		FILE* code = Prog_to_code(prog);

		double res = Read_code(code);

		printf("\nThe result is: %lf\n", res);

		return 0;
	}
}