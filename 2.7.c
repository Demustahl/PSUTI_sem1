#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long int factorial_2n(long int n)
{
	int count = 1;
	long int res = 1;
	n *= 2;
	while (count <= n) {
		res *= count;
		count++;
	}
	return res;
}

double sum_series(double x)
{
	double sum = 0, sum1, e = pow(10,-6);
	long int f, n = 0;
	do {
		f = factorial_2n(n);
		sum1 = (double)(pow(-1, n) * pow(2, 2*n-1) * pow(x, 2*n))/(double)f;
		sum += sum1;
		n++;
		printf("fac = %ld sum = %lf     ", sum);
	} while (fabs(sum1) > e); 
	return sum + 0.5;
}


int main()
{
	double y, x, sum;
	puts("Enter X in the range [0.1; 0.8]: ");
	scanf("%lf", &x);
	// Вычислим значение функции y(x)
	y = pow(cos(x), 2);
	printf("y = %.10lf\n", y);
	// Вычислим значение суммы бесконечного ряда
	sum = sum_series(x);
	printf("\nSUM = %lf", sum);
	return 0;
}

