#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>


const int MAXLEN = 9000;
const int MAXLINES = 1000;
const int STACKOVERWHELM = -100;
const int GP_WRONGINPUT = -10;
const int MAXSIZE = 50;
const int ERROR_END_OF_FILE = -20;
const int ERROR_FIND_BEGINNING = -30;


//--------------------------------------------------
//* comparator, compares lines in reverse order
//--------------------------------------------------

int Strcmp_reverse(const void* s1, const void* s2);


//--------------------------------------------------
//! Saves symbols from poem
//!
//! @param[in] fp pointer to file
//! @param[out] text massive with symbols
//!
//! @return length of line or GPO_WRONGINPUT if input is incorrect
//--------------------------------------------------

int Getpoem(FILE* fp, char* Text);


//--------------------------------------------------
//! Reads lines in Lineptr[]
//!
//! @param[in] text - massive with symbols
//! @param[in] nsym - number of symbols in text
//! @param[out] Lineptr[] massive where we read
//! 
//! @return number of lines
//--------------------------------------------------

int Getptr(char* Lineptr[], char* text);


//--------------------------------------------------
//! prints lines from Lineptr[]
//!
//! @param[in] Lineptr[] what we print
//! @param[in] Numberlines number of lines
//!
//! @return void
//--------------------------------------------------

void Writelines(char* Lineptr[], const int numberlines, FILE* fp);


//--------------------------------------------------
//! strcmp from <stdlib.h>, but input is const void*, const void*
//--------------------------------------------------

int Strcmp(const void *s1, const void *s2);


//--------------------------------------------------
//! Compares result of expression with True
//! 
//! @param[in] name name of test
//! @param[in] expression what we compare
//! 
//! @return true or false
//--------------------------------------------------

bool Test_function(const char* name, int expression);


//--------------------------------------------------
//! Unit tests for Strcmp and Strcmp_reverse
//--------------------------------------------------

void TestComparators(void);
