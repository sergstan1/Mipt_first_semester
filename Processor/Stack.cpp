#include "Stack.h"
#include "Log.h"

extern StackCanary CANARYVALUE = 0xAFBCDEFA9820;

static bool Overflow_Checker = false;
static bool Underflow_Checker = false;


int StackCtor(Stack* stack)
{
	assert(START_SIZE > 0);

	Overflow_Checker = false;
	Underflow_Checker = false;

	stack->data = (StackElem*)calloc(START_SIZE, sizeof(StackElem));

	if (stack->data == NULL)
	{
		Overflow_Checker = true;
		return 1;
	}

	stack->size = 0;
	stack->capacity = START_SIZE;

	stack->canary_back = CANARYVALUE;
	stack->canary_front = CANARYVALUE;

	return 0;
}


void StackGrow(Stack* stack)
{
	StackElem* temp = stack->data;

	stack->capacity *= MULTIPLICATOR;

	if ((temp = (StackElem*)(realloc(stack->data, (stack->capacity) * sizeof(StackElem)))) == NULL)
	{
		Overflow_Checker = true;
		return;
	}

	stack->data = temp;
}


void Push(Stack* stack, StackElem data)
{
	if (stack->size == stack->capacity)
		StackGrow(stack);

	stack->data[stack->size] = data;
	(stack->size)++;
}


StackElem Pop(Stack* stack)
{
	if (stack->size == 0)
	{
		Underflow_Checker = true;
		return NULL;
	}
	else
	{
		stack->size--;

		StackElem temp1 = stack->data[stack->size];
		StackElem* temp2 = NULL;

		if (stack->size < stack->capacity / 2 && stack->capacity > 10)
		{
			stack->capacity /= MULTIPLICATOR;

			if (!(temp2 = (StackElem*)realloc(stack->data, stack->capacity * sizeof(StackElem))))
				exit(1);

			stack->data = temp2;

		}
		return temp1;
	}
}


StackError Stack_Errors(Stack* stack)
{
#define STACK_ERROR_WITH_DESCRIPTION(error) {error, #error}

	if (stack == NULL)
	{
		return STACK_ERROR_WITH_DESCRIPTION(NULL_POINTER_TO_STACK);
	}

	if ((stack->canary_back != CANARYVALUE) || ((stack->canary_front != CANARYVALUE)))
	{
		return STACK_ERROR_WITH_DESCRIPTION(DEAD_CANARY);
	}
	if (stack->data == NULL)
	{
		return STACK_ERROR_WITH_DESCRIPTION(NULL_POINTER_TO_DATA);
	}

	if (stack->size > stack->capacity)
	{
		return STACK_ERROR_WITH_DESCRIPTION(SIZE_GREATER_THAN_CAPACITY);
	}

	if (!stack->capacity)
	{
		return STACK_ERROR_WITH_DESCRIPTION(CAPACITY_IS_ZERO);
	}
	if (Underflow_Checker == true)
	{
		return STACK_ERROR_WITH_DESCRIPTION(STACK_UNDERFLOW);
	}
	if (Overflow_Checker == true)
	{
		return STACK_ERROR_WITH_DESCRIPTION(STACK_OVERFLOW);
	}

	if (!Verify_Data(stack))
	{
		return STACK_ERROR_WITH_DESCRIPTION(INVALID_DATA);
	}

	return STACK_ERROR_WITH_DESCRIPTION(OK);

#undef STACK_ERROR_WITH_DESCRIPTION
}


void Verify_Stack(Stack* stack)
{
	StackError error = Stack_Errors(stack);

	if (error.code)
	{
		Stack_Dump(stack, &error);

		fclose(LogFile);

		abort();
	}
}


bool Verify_Data(Stack* stack)
{
	assert(stack != NULL);

	for (int i = 0; i < stack->size; i++)
	{
		if (!isfinite(stack->data[i]))
			return false;
	}
	return true;
}


void Stack_Dtor(Stack* stack)
{
	Verify_Stack(stack);

	free(stack->data);
}

void Stack_Dump(const Stack* stack, const StackError* stackerror)
{
	assert(stackerror);

	switch (stackerror->code)
	{
	case OK:
	{
		logging("STACK_DUMP: status #%d, %s\n"
			"Stack [%p]\n"
			"{\n"
			"\tsize     = %zu\n"
			"\tcapacity = %zu\n"
			"\tdata [%p]\n"
			"\t{\n", stackerror->code, stackerror->description, stack, stack->size, stack->capacity, stack->data);
		for (int i = 0; i < stack->size; ++i) logging("\t\t[%zu] = %f\n", i, stack->data[i]);
		logging("\t}\n"
			"}\n");
		return;
	}
	case DEAD_CANARY:
	case STACK_UNDERFLOW:
	case NULL_POINTER_TO_DATA:
	{
		logging("STACK_DUMP: status #%d, %s\n"
			"Stack [%p]\n"
			"{\n"
			"\tsize     = %zu\n"
			"\tcapacity = %zu\n"
			"\tdata [%p]\n"
			"}\n", stackerror->code, stackerror->description, stack, stack->size, stack->capacity, stack->data);
		return;
	}
	case NULL_POINTER_TO_STACK:
	{
		logging("STACK_DUMP: status #%d, %s\n"
			"Stack [%p]\n", stackerror->code, stackerror->description, stack);
		return;
	}
	case INVALID_DATA:
	{
		logging("STACK_DUMP: status #%d, %s\n"
			"Stack [%p]\n"
			"{\n"
			"\tsize     = %zu\n"
			"\tcapacity = %zu\n"
			"\tdata [%p]\n"
			"\t{\n", stackerror->code, stackerror->description, stack, stack->size, stack->capacity, stack->data);
		for (int i = 0; i < stack->size; ++i) logging("\t\t[%zu] = %f\n", i, stack->data[i]);
		logging("\t}\n"
			"}\n");
		return;
	}
	case SIZE_GREATER_THAN_CAPACITY:
	{
		logging("STACK_DUMP: status #%d, %s\n"
			"Stack [%p]\n"
			"{\n"
			"\tsize     = %zu\n"
			"\tcapacity = %zu\n"
			"\tdata [%p]\n"
			"\t{\n", stackerror->code, stackerror->description, stack, stack->size, stack->capacity, stack->data);
		for (int i = 0; i < stack->size; ++i) logging("\t\t*[%10zu] = %f\n", i, stack->data[i]);
		for (int i = stack->size; i < stack->capacity; ++i) logging("\t\t[%10zu] = %f\n", i, stack->data[i]);
		logging("\t}\n"
			"}\n");
		return;
	}
	}
}