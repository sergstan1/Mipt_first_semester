#ifndef TEXT_H
#define TEXT_H

#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int STACKOVERWHELM = -100;
const int GP_WRONGINPUT = -10;
const int ERROR_END_OF_FILE = -20;
const int ERROR_FIND_BEGINNING = -30;
const int EPS = 2;
const int MAXLABEL = 100;


//--------------------------------------------------
//! prints lines from Lineptr[]
//!
//! @param[in] Lineptr[] what we print
//! @param[in] Numberlines number of lines
//!
//! @return void
//--------------------------------------------------

void Writelines(char* Lineptr[], const int numberliens, FILE* fp);


//--------------------------------------------------
//! Saves symbols from file
//!
//! @param[in] fp pointer to file
//! @param[out] text massive with symbols
//!
//! @return length of line or GPO_WRONGINPUT if input is incorrect
//--------------------------------------------------

int Getfile(FILE* fp, char** text);


//--------------------------------------------------
//! Reads lines in Lineptr[]
//!
//! @param[in] text - massive with symbols
//! @param[in] nsym - number of symbols in text
//! @param[out] Lineptr[] massive where we read
//! 
//! @return number of lines
//--------------------------------------------------


int Getptr_s(char* Lineptr[], char* text);

//--------------------------------------------------
//! Counts number of lines, divided by symbs in text
//
// @param[in] str - where we count
// @param[in] nsymb length of str
//
// @return number of lines
//--------------------------------------------------

int Strcount(char* str, char* symb);

#endif
