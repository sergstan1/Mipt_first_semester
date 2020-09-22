#include <stdio.h>
#include <math.h>
#include <assert.h>

#define CASQE_INFINITY_SOLUTIONS -1

double Eps = 1e-6;

int iszero(double a)
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


int count_and_solve_quadratic_equation(double a, double b, double c, double* x1, double* x2)
{
	assert(x1 != NULL);
	assert(x2 != NULL);
	assert(x1 != x2);

	if (iszero(a))
	{
		if (iszero(b))
		{
			if (iszero(c))
				return CASQE_INFINITY_SOLUTIONS;
			else
				*x1 = 0;
			return 1;
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
		else if (iszero(discriminant))
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


int main()
{
	printf("# Solve quadratic equation\n");
	printf("# (c) Sergey Stanko\n\n");

	printf("# Enter a, b, c :\n");

	double a = 0, b = 0, c = 0;
	scanf_s("%lf %lf %lf", &a, &b, &c);
	double x1 = 0, x2 = 0;

	int quantity = count_and_solve_quadratic_equation(a, b, c, &x1, &x2);

	switch (quantity)
	{
	case (0):
		printf("No solutions\n");
		break;
	case(1):
		printf("%lg", x1);
		break;
	case(2):
		printf("%lg %lg", x1, x2);
		break;
	case(CASQE_INFINITY_SOLUTIONS):
		printf("Infinit number of solutions\n");
		break;
	default:
		printf("ERROR\n");
		break;
	}
	return 0;
}
