#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// M_PI;

double sum_series(double x)
{
	double sum = 0, sum1, e = pow(10,-6);
	long int n = 1;
	do {
		sum1 = (pow(x, n)*cos((n*M_PI)/3))/(double)n;
		sum += sum1;
		n++;
		printf("sum = %lf     ", sum);
	} while (fabs(sum1) > e); 
	return sum;
}

int main()
{
	double y, x, sum;
	puts("Enter X in the range [0.1; 0.8]: ");
	scanf("%lf", &x);
	// Вычислим значение функции y(x)
	y = -0.5*log(1-2*x*cos(M_PI/3)+pow(x, 2));
	printf("y = %.10lf\n", y);
	// Вычислим значение суммы бесконечного ряда
	sum = sum_series(x);
	printf("\nSUM = %lf", sum);
	return 0;
}

