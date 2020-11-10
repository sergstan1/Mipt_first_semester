#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>


enum command_code
{
	zero,
	mul,
	divis,
	add,
	sub,
	push,
	pop,
	in,
	out,
	halt
};


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


void Check_scanf(int result, double* a);


#endif