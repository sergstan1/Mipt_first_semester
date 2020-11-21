#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>
#include <math.h>

const int STARTSIZE = 10;

enum command_code
{
	mul = 1,
	divis,
	add,
	sub,
	push,
	pop,
	in,
	out,
	label,
	jump,
	jae,
	ja,
	jbe,
	jb,
	je,
	jne,
	sqaure,
	halt
};

enum push_pop_command
{
	reg = 1,
	number
};

enum registers
{
	a = 1,
	b,
	c
};

enum labels
{
	next,
	stop,
	teleport
};

struct struct_label
{
	const char* name = {};

	char* pos = {};

	size_t repeat_status = 0;
};


static double ax = 0, bx = 0, cx = 0;


//----------------------------------------------------
//! Transforms file with commands to assembler file
//!
//! @param[in] pointer to file with commands
//! 
//! @return pointer to new file
//----------------------------------------------------

FILE* Prog_to_code(FILE* prog);


//----------------------------------------------------
//! Transforms asm file to code
//
//! @param[in] pointer to asm file
//!
//! @return pointer to file with code
//----------------------------------------------------

FILE* Read_commands(FILE* input);


//----------------------------------------------------
//! Reads code and compiles it
//!
//! @param[in] pointer to file with code
//!
//! @return result of work of a programm or NULL,
//!      if there are more then 1 result of programm.
//----------------------------------------------------

double Read_code(FILE* fp);


//--------------------------------------------------
//! Check, that input is correct
//!
//! @param[in] result  number of correct inputs
//! @param[in] a what we scan
//!
//! @return void
//--------------------------------------------------

void Check_scanf(int result, double* a);


//--------------------------------------------------
//! Transfer pointer on sizeof(int) forward
//! 
//! @param[in] pbytes - address of pointer to massiv
//! @param[out] value return int value of char massive
//!
//! @return void
//--------------------------------------------------

void Tp(char** pbytes, int value);


//-----------------------------------------------------------
//! Compares str with label
//!
//! @param[in] str
//! @param[in] labels[] massive where are labels
//! 
//! @return 0 or natural number if if label of -1 if is not
//-----------------------------------------------------------

int Label_cmp(char* str, struct_label labels[]);


//-----------------------------------------------------------
//! Recomplies code to search label
//!
//! @param[in] pointer to the start of the code
//! 
//! @return void
//!
//! @note in massive with labels put repeat_status = 1
//-----------------------------------------------------------

char* Transport(char* rip);


#endif