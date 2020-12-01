#define _CRT_SECURE_NO_WARNINGS

#include "tree.h"

Node* Tree_ctr(int* pi, char** lineptr, Node* pnode)
{
    size_t j = 0;
    while (isspace(lineptr[*pi][j]))
        j++;

    if (lineptr[*pi][j] == '\0')
    {
        (*pi)++;

        j = 0;
        while (isspace(lineptr[*pi][j]))
            j++;
    }

    if ((lineptr[*pi][j]) == ')')
    {
        return NULL;
    }


    if ((lineptr[*pi][j]) == '(')
    {
        pnode = (Node*)calloc(1, sizeof(Node));
        if (pnode == NULL)
        {
            printf("No memory\n");

            exit(1);
        }
        (*pi)++;

        j = 0;
        while (isspace(lineptr[*pi][j]))
            j++;

        pnode->name = &lineptr[*pi][j];
        (*pi)++;

        pnode->left = Tree_ctr(pi, lineptr, pnode->left);
    }   

    j = 0;

    while (isspace(lineptr[*pi][j]))
        j++;

    if (lineptr[*pi][j] == '\0')
    {
        (*pi)++;

        j = 0;
        while (isspace(lineptr[*pi][j]))
            j++;
    }

    if (lineptr[*pi][j] == '(' && pnode->left != NULL)
    {

        pnode->right = Tree_ctr(pi, lineptr, pnode->right);
    }

    j = 0;

    if (lineptr[*pi] != NULL)
    {
        while (isspace(lineptr[*pi][j]))
            j++;
        if (lineptr[*pi][j] == '\0')
        {
            (*pi)++;

            j = 0;
            while (isspace(lineptr[*pi][j]))
                j++;
        }
    }

    if (lineptr[*pi][j] == ')')
    {
        (*pi)++;

        return pnode;
    }
}


void Tree_print(struct Node* tree)
{
    if (tree != NULL)
    {
        Tree_print(tree->left);
        printf("%s\n", tree->name);
        Tree_print(tree->right);
    }
}


void Questions(Node* node)
{

    if (node->right == NULL && node->left == NULL)
    {
        printf("The answer is %s", node->name);

        return;
    }

    printf("Is it %s\n", node->name);

    char answer[4] = {};

    scanf("%s", answer);

    if (strcmp(answer, "YES") == 0 || strcmp(answer, "Yes") == 0 || strcmp(answer, "yes") == 0)
        Questions(node->right);
    else if (strcmp(answer, "NO") == 0 || strcmp(answer, "No") == 0 || strcmp(answer, "no") == 0)
        Questions(node->left);
    else
    {
        printf("Uknow answer\n");

        exit(1);
    }

    return;
}