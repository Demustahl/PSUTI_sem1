#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Фун. для вычисления определенного интеграла методом Ньютона
double integral_Newtons_method(double a, double b, double (*func)(double))
{
	int i = 1;
	double xb = a, xe = b, N = 15, newton = 0;
	double dx = (b - a)/N;
	for (double x = xb; x <= xe; x += dx) {
		if (x == xb) {
			newton += func(x);
		}
		else if (x == xe) {
			newton += func(x);
		}
		else if (i % 3 == 0) {
			newton += func(x)*2;
			i++;
		}
		else {
			newton += func(x)*3;
			i++;
		}
	}
	return ((3*(b - a))/(8*15))*newton;
}

// Фун. для передачи функции 1
double f_1(double x)
{
	return cos(x)/(1 + pow(sin(x), 2));
}

// Фун. для передачи функции 2
double f_2(double x)
{
	return x*exp(x + 1);
}

int main()
{
	puts("We calculate a definite integrals of \
two functions using Newton's method.");
	puts("The definite integral of the first function: ");
	printf("%lf\n", integral_Newtons_method(1, 5, f_1));
	puts("The definite integral of the second function: ");
	printf("%lf\n", integral_Newtons_method(-1, 3, f_2));
	return 0;
}