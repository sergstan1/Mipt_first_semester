#include <stdio.h>
#include <math.h>

float eps= 1e-6;

int count_and_solve_quadratic_equation(float a, float b, float c, float* x1, float* x2)
{
	if ((a < eps && a > 0) || ((a > -1*eps) && a < 0)) {
		if (b == 0) {
			if (c == 0)
				return -1;
			else
				return 0;
		}
		else
		{
			*x1 = -c / a;
			return 1;
		}
	}
	else {
		float Discriminant = (b * b - 4 * a * c);

		if (Discriminant < 0)
			return 0;
		else if ((Discriminant < eps && Discriminant > 0))/*if (Discriminant == 0)*/
		{
			*x1 = -b / (2 * a);
			return 1;
		}
		else
		{
			*x1 = (-b + sqrt(Discriminant)) / (2 * a);
			*x2 = (-b - sqrt(Discriminant)) / (2 * a);
			return 2;
		}
	}
}

main()
{
	printf("# Solve quadratic equation\n");
	printf("# (c) Sergey Stanko\n\n");

	printf("# Please, enter a, b, c :\n");

	float a, b, c;
	scanf_s("%f %f %f", &a, &b, &c);
	float x1, x2; /*Solutions*/
	x1 = x2 = 0;

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
	case(-1):
		printf("Infinit number of solutions\n");
		break;
	default:
		printf("ERROR\n");
		break;
	}
	return 0;
}