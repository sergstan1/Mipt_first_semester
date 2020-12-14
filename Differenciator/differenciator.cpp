#include "differenciator.h"
#include "tree.h"


Node* Deriative(Node* pnode)
{
	size_t i = 0;
	while (isspace((pnode->name)[i]))
	{
		i++;
	}

	Node* npnode = {};

	if (pnode != NULL)
	{
		if ((pnode->name)[i] == '*')
		{
			npnode = Tree_add("+", npnode);
			npnode->left = Tree_add("*", npnode->left);
			npnode->right = Tree_add("*", npnode->right);

			npnode->left->right = pnode->left;
			npnode->right->right = pnode->right;

			npnode->left->left = Deriative(pnode->right);
			npnode->right->left = Deriative(pnode->left);
		}
		else if ((pnode->name)[i] == '+')
		{
			npnode = Tree_add("+", npnode);

			npnode->left = Deriative(pnode->left);
			npnode->right = Deriative(pnode->right);
		}
		else if ((pnode->name)[i] == '-')
		{
			npnode = Tree_add("-", npnode);

			npnode->left = Deriative(pnode->left);
			npnode->right = Deriative(pnode->right);
		}
		else if (strcmp(&(pnode->name)[i] + '\0', "sin") == 0)
		{
			npnode = Tree_add("*", npnode);

			npnode->right = Tree_add("cos", npnode->right);
			npnode->right->left = pnode->left;

			npnode->left = Deriative(pnode->left);
		}
		else if (strcmp(&(pnode->name)[i] + '\0', "cos") == 0)
		{
			npnode = Tree_add("*", npnode);

			npnode->right = Tree_add("*", npnode->right);
			npnode->right->left = Tree_add("sin", npnode->right->left);
			npnode->right->right = Tree_add("-1", npnode->right->right);
			npnode->right->left->left = pnode->left;

			npnode->left = Deriative(pnode->left);
		}
		else if (isdigit((pnode->name)[i]) || (pnode->name)[i] == '-' && isdigit((pnode->name)[i + 1]))
		{
			npnode = Tree_add("0", npnode);
		}
		else if ((pnode->name)[i] == 'x')
		{
			npnode = Tree_add("1", npnode);
		}
		else if ((pnode->name)[i] == '^')
		{
			char buffer[MAXLEXEM] = {};
			npnode = Tree_add("*", npnode);

			npnode->right = Tree_add(pnode->right->name, npnode->right);

			npnode->left = Tree_add("^", npnode->left);
			npnode->left->left = Tree_add(pnode->left->name, npnode->left->left);
			npnode->left->right = Tree_add(_itoa(atoi(pnode->right->name) - 1, buffer, 10), npnode->left->right);
		}
		else if (strcmp(&(pnode->name)[i] + '\0', "ln") == 0)
		{
			npnode = Tree_add("*", npnode);

			npnode->left  = Deriative(pnode->left);
			npnode->right = Tree_add("^", npnode->right);

			npnode->right->right = Tree_add("-1", npnode->right->right);
			npnode->right->left = pnode->left;
		}
		else if (strcmp(&(pnode->name)[i] + '\0', "exp") == 0)
		{
			npnode = Tree_add("*", npnode);

			npnode->left = Deriative(pnode->left);
			npnode->right = Tree_add("exp", npnode->right);

			npnode->right->left = pnode->left;
		}
		else
		{
			printf("Uknow function\n");

			exit(1);
		}
		return npnode;
	}
}