#include <stdio.h>
#include <math.h>
#include <assert.h>

#define CASQE_INFINITY_SOLUTIONS -1

double Eps = 1e-6;

void Test_Count_and_solve_quadratic_equation(void);

int Iszero(double a);

int Count_and_solve_quadratic_equation(double a, double b, double c, double* x1, double* x2);

int Test_function(const char* name, int expression);

int main(void)
{
	printf("# Solve quadratic equation\n");
	printf("# (c) Sergey Stanko\n\n");

	printf("# Enter a, b, c :\n");

	double a = 0, b = 0, c = 0;
	scanf_s("%lf %lf %lf", &a, &b, &c);
	double x1 = 0, x2 = 0;

	int quantity = Count_and_solve_quadratic_equation(a, b, c, &x1, &x2);

	switch (quantity)
	{
	case (0):
		printf("No solutions\n");
		break;
	case(1):
		printf("Square equation has 1 route: %lg\n", x1);
		break;
	case(2):
		printf("Square equation has 2 routes: %lg and %lg\n", x1, x2);
		break;
	case(CASQE_INFINITY_SOLUTIONS):
		printf("Infinit number of solutions\n");
		break;
	default:
		printf("ERROR, number of solutions = %d\n", quantity);
		return 1;
	}
	Test_Count_and_solve_quadratic_equation();
	return 0;
}


//--------------------------------------------------
//! Compare input with zero with certain accuracy
//!
//! @param[in] a what we compare
//!
//! @return 1(True = 0) or 0(False != 0)
//!
//! @note accuracy = 10^(-6)
//--------------------------------------------------


int Iszero(double a)
{
	if ((a < Eps && a >= 0) || ((a > -1 * Eps) && a <= 0))
		return 1;
	else
		return 0;
}


//--------------------------------------------------
//! Solves a quadratic equation ax^2 + bx + c
//!
//! @param[in] a quadratic coefficent
//! @param[in] b linear coefficent
//! @param[in] c free coefficent
//! @param[out] x1 first solution
//! @param[out] x2 second solution
//!
//! @return number of routes
//!
//! @note in case infinite routes,
//!               returns CASQE_INFINITY_SOLUTIONS.
//--------------------------------------------------


int Count_and_solve_quadratic_equation(double a, double b, double c, double* x1, double* x2)
{
	assert(x1 != NULL);
	assert(x2 != NULL);
	assert(x1 != x2);

	if (Iszero(a))
	{
		if (Iszero(b))
		{
			if (Iszero(c))
				return CASQE_INFINITY_SOLUTIONS;
			else
				return 0;
		}
		else
		{
			*x1 = -c / b;
			return 1;
		}
	}
	else
	{
		double discriminant = (b * b - 4 * a * c);

		if (discriminant < 0)
			return 0;
		else if (Iszero(discriminant))
		{
			*x1 = -b / (2 * a);
			return 1;
		}
		else
		{
			*x1 = (-b + sqrt(discriminant)) / (2 * a);
			*x2 = (-b - sqrt(discriminant)) / (2 * a);
			return 2;
		}
	}
}


//--------------------------------------------------
//! Compares result of expression with True
//! 
//! @param[in] name name of test
//! @param[in] expression what we compare
//! 
//! @return 1 if true or 0 if false
//--------------------------------------------------


int Test_function(const char* name, int expression)
{
	if (expression)
	{
		printf("test %s passed\n", name);
		return true;
	}
	else
	{
		printf("test %s failed\n", name);
		return false;
	}
}


//--------------------------------------------------
//! Tests Count_and_solve_quadratic_equation
//--------------------------------------------------


void Test_Count_and_solve_quadratic_equation(void)
{
	printf("Unit tests:\n");

	double x1 = 0, x2 = 0;

	int number_tests_passed = 0, number_tests_failed = 0;

#define TEST(name, expression) ((Test_function(name, expression)) ? ++number_tests_passed : ++number_tests_failed)

	TEST("infinite number of roots",
		Count_and_solve_quadratic_equation(0, 0, 0, &x1, &x2) == CASQE_INFINITY_SOLUTIONS);
	TEST("0 roots, constant equation",
		Count_and_solve_quadratic_equation(0, 0, 1, &x1, &x2) == 0);
	TEST("0 roots, quadratic equation",
		Count_and_solve_quadratic_equation(1, 1, 1, &x1, &x2) == 0);
	TEST("1 root, linear equation, number of roots",
		Count_and_solve_quadratic_equation(0, 1, 1, &x1, &x2) == 1);

#undef TEST

	printf("Finished testing Count_and_solve_quadratic_equation function: %d tests passed, %d tests failed. The"
		"total number of tests was: %d\n",
		number_tests_passed, number_tests_failed, number_tests_passed + number_tests_failed);
}

