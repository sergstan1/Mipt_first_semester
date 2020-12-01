#pragma once

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


typedef struct Node
{
    char* name;
    struct Node* left;  
    struct Node* right;
} Node;

Node* Tree_ctr(int* pi, char** lineptr, Node* pnode);


void Tree_print(Node* tree);


void Questions(Node* node);