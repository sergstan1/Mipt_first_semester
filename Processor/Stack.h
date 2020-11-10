#ifndef STACK_H
#define STACK_H


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

typedef unsigned long long StackCanary;
typedef double StackElem;

//----------------------------------------------------
//! A number on what size of the stack is multiplied
//----------------------------------------------------

const int MULTIPLICATOR = 2;


//----------------------------------------------------
//! Start size of the stack
//----------------------------------------------------

const int START_SIZE = 10;


//----------------------------------------------------
//! List of errors in the stack
//----------------------------------------------------

enum error_code
{
	OK,
	DEAD_CANARY,
	NULL_POINTER_TO_STACK,
	NULL_POINTER_TO_DATA,
	INVALID_DATA,
	STACK_OVERFLOW,
	STACK_UNDERFLOW,
	SIZE_GREATER_THAN_CAPACITY,
	CAPACITY_IS_ZERO
};


//----------------------------------------------------
//! Stack
//----------------------------------------------------

struct Stack
{
	StackCanary canary_front;

	StackElem* data;
	size_t size;
	size_t capacity;

	StackCanary canary_back;
};

//----------------------------------------------------
//! Structure, was made to descript errors
//----------------------------------------------------

struct StackError {
	error_code code;
	const char* description;
};


//----------------------------------------------------
//! Creates stack
//! @param[in]  pointer to stack
//! @param[out] stack with Starting size
//----------------------------------------------------

int StackCtor(Stack* stack);


//----------------------------------------------------
//! Increases size by two times
//!
//! @param[in] pointer to stack
//----------------------------------------------------


void StackGrow(Stack* stack);


//----------------------------------------------------
//! Puts data into the stack
//!
//! @param[in] pointer to stack
//! @param[in] what we put in the stack
//----------------------------------------------------

void Push(Stack* stack, StackElem data);


//----------------------------------------------------
//! Gets data from the stack
//! 
//! @param[in] pointer to stack
//!
//----------------------------------------------------

StackElem Pop(Stack* stack);


//----------------------------------------------------
//! List of errors in the stack
//----------------------------------------------------

StackError Stack_Errors(Stack* stack);


//----------------------------------------------------
//! If there are errors in the stack, aborts a programm
//----------------------------------------------------

void Verify_Stack(Stack* stack);


//----------------------------------------------------
//! Verifies data in the stack with isfinite 
//----------------------------------------------------

bool Verify_Data(Stack* stack);


//----------------------------------------------------
//! Logs what is happening to our stack
//----------------------------------------------------

void Stack_Dump(const Stack* stack, const StackError* stackerror);


#endif STACK_H