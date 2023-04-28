#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() 
{
	long int denominator, numerator, a, A, p = 2, ps, yes, colvo = 0;
	puts("Enter A: ");
	scanf("%ld", &A);
	puts("Suitable numbers:");
	for (a = 1; a != A; a++) {
		denominator = pow(a, 3) + 11*a;
		numerator = pow(a, 4) + 12*pow(a, 2) - 5;
		while ((p < numerator) && (p < denominator) && (p >= 0)) {
			yes = 1; ps = 2;
			while ((ps <= (p/2 + 1)) && (p >= 0) && (p <= 10)) {
				if (p % ps == 0) {
					yes = 0;
				}
				if (p == 2) yes = 1;
				ps++;
			}
			if ((yes == 1) && (denominator % p == 0) && (numerator % p == 0)) {
				colvo += 1;
				printf("colvo = %ld; a=%ld: %ld\n", colvo, a, p);
			}
			p++;
		}
		printf("%ld  ", a);
	}
	printf("\ncolvo = %ld\n", colvo);
	return 0;
}