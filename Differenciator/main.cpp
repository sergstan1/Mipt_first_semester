#include "text.h"
#include "tree.h"
#include "differenciator.h"


int main(int argc, char** argv)
{
	printf("# Differenciator\n");
	printf("# (c) Sergey Stanko\n\n");


	if (argc <= 1)
	{
		printf("No command line arguments\n");

		return 1;
	}

	FILE* fp = fopen(argv[1], "rb");
	if (fp == NULL)
	{
		printf("Could not open file\n");

		return 1;
	}

	int nlines = 0;
	char** lineptr = {};
	lineptr = Read(fp, &nlines);

	int i = 0;
	Node* node = {};

	node = Tree_ctr(&i, lineptr, node);

	Node* deriative = {};

	deriative = Deriative(node);

	fp = fopen("Answer.txt", "w");
	if (fp == NULL)
	{
		printf("Could not open file, where write an answer\n");

		exit(1);
	}

	Tree_print(deriative, fp);

	printf("Success\n");

	return 0;
}