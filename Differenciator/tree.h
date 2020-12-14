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


const int MAXTREE = 10000;


//---------------------------------------------------------------------
//! Creates a tree, operating on brackets
//!
//! @param[in] *pi = 0 pointer which transfers in recursive functions
//! @param[in] lineptr massive where are words with brackets
//! @param[out] pnode a copy of pointer to tree
//!
//! @return pointer to tree
//---------------------------------------------------------------------

Node* Tree_ctr(int* pi, char** lineptr, Node* pnode);


//---------------------------------------------------------------------
//! Prints a tree in the file
//! 
//! @param[in] tree which we print
//! @param[in] a pointer to file where we print
//!
//! @return void
//---------------------------------------------------------------------

void Tree_print(struct Node* tree, FILE* fp);


//---------------------------------------------------------------------
//! Checks string, if it consists only with spaces, increasing pi
//!
//! @param[in] pi a counter in strings which we increase
//! @param[in] lineptr massive with pointers to strings,
//!                                          which we check
//! @param[in] *pj a counter to position in the string
//!
//! @return void
//---------------------------------------------------------------------

void Check_zero(int* pi, char** lineptr, size_t* pj);


//---------------------------------------------------------------------
//! Adds a new single node
//!
//! @param[in] value what we put in the node
//! @param[out] pnode a copy of pointer to tree
//!
//! @return pointer to tree
//---------------------------------------------------------------------

Node* Tree_add(const char* value, Node* pnode);