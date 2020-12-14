#define _CRT_SECURE_NO_WARNINGS

#include "tree.h"

Node* Tree_ctr(int* pi, char** lineptr, Node* pnode)
{
    size_t j = 0;
    while (isspace(lineptr[*pi][j]))
        j++;

    Check_zero(pi, lineptr, &j);

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

        Check_zero(pi, lineptr, &j);

        if ((lineptr[*pi][j]) == '(')
        {
            pnode->left = Tree_ctr(pi, lineptr, pnode->left);
        }

        pnode->name = &lineptr[*pi][j];
        (*pi)++;

        if (pnode->left == NULL)
        {
            pnode->left = Tree_ctr(pi, lineptr, pnode->left);
        }
    }   

    j = 0;

    while (isspace(lineptr[*pi][j]))
        j++;

    Check_zero(pi, lineptr, &j);

    if (lineptr[*pi][j] == '+' || lineptr[*pi][j] == '*' || lineptr[*pi][j] == '-' || lineptr[*pi][j] == '^')
    {
        pnode->name = &lineptr[*pi][j];
        (*pi)++;
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

        Check_zero(pi, lineptr, &j);
    }

    Check_zero(pi, lineptr, &j);

    if (lineptr[*pi][j] == ')')
    {
        (*pi)++;

        return pnode;
    }
}


void Tree_print(struct Node* tree, FILE* fp)
{
    if (tree != NULL)
    {
        fprintf(fp, "(");
        Tree_print(tree->left, fp);
        fprintf(fp, "%s", tree->name);
        Tree_print(tree->right, fp);
        fprintf(fp, ")");
    }
}


void Check_zero(int* pi, char** lineptr, size_t* pj)
{
    if (lineptr[*pi][*pj] == '\0')
    {
        (*pi)++;

        *pj = 0;
        while (isspace(lineptr[*pi][*pj]))
            (*pj)++;
    }
}


Node* Tree_add(const char* value, Node* pnode)
{
    if (pnode == NULL)
    {
        pnode = (Node*)calloc(1, sizeof(Node));
        if (pnode == NULL)
        {
            printf("Could not allocate memory to new node, while diffirincating function\n");

            exit(1);
        }

        char* temp = (char*)calloc(strlen(value), sizeof(char));
        strcpy(temp, value);
        pnode->name = temp;
    }
    else
    {
        printf("Node is not empty\n");

        exit(1);
    }
}