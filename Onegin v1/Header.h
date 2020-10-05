#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 10000
#define MAXLINES 5000
#define STACKOVERWHELM -100
#define GPO_WRONGINPUT -10
#define MAXSIZE 100


//--------------------------------------------------
//! Shows how many errors were in Getpoemline
//--------------------------------------------------

int Number_of_errors = 0;


//--------------------------------------------------
//! if true, programm returns an error
//--------------------------------------------------

bool Error_warning = false;


//--------------------------------------------------
//! Shows how many lines were readen
//--------------------------------------------------

int Numberlines = 0;


//--------------------------------------------------
//! Massive, where we save pointers to lines
//--------------------------------------------------

char* Lineptr[MAXLINES];


//--------------------------------------------------
//! Saves line from poem
//!
//! @param[in] limit maximum length of line
//! @param[in] fp pointer to file
//! @param[out] pline pointer to line from file
//!
//! @return length of line or GPO_WRONGINPUT if input is incorrect
//!
//! @note if wrong input prints line where was an error
//--------------------------------------------------

int Getpoemline(char* pline, const int limit, FILE* fp);


//--------------------------------------------------
//! Reads lines in Lineptr[]
//!
//! @param[in] maxlines maximum number of lines
//! @param[in] *fp pointer to file
//! @param[out] Lineptr[] massive where we read
//! 
//! @return number of lines or STACKOVERWHELM if too many lines
//--------------------------------------------------

int Readlines(char* Lineptr[], const int maxlines, FILE* fp);


//--------------------------------------------------
//! prints lines from Lineptr[]
//!
//! @param[in] Lineptr[] what we print
//! @param[in] Numberlines number of lines
//!
//! @return void
//--------------------------------------------------

void Writelines(char* Lineptr[], int Numberlines);



//--------------------------------------------------
//! strcmp from <stdlib.h>, but input is const void*, const void*
//--------------------------------------------------

int Strcmp(const void *s1, const void *s2);

