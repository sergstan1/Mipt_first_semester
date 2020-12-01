#include "text.h"
#include "tree.h"
#include "C:\Users\Sergstan\Desktop\Akinator\Akinator\Akinator\Dotter\Dotter.h"

int main(int argc, char** argv)
{
	printf("# Akinator\n");
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

	Questions(node);

	dtBegin("Example.dot");

	dtNode(0, node->name);
	dtNode(1, node->left->name);
	dtNode(2, node->right->name);
	dtNode(3, node->left->left->name);
	dtNode(4, node->left->right->name);

	dtLink(0, 1, "NO");
	dtLink(0, 2, "YES");
	dtLink(1, 3, "NO");
	dtLink(1, 4, "YES");

	dtEnd();

	dtRender("Example.dot");

	return 0;
}