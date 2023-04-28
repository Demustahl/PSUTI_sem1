#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	float x1, x2, x3, y1, y2, y3, a, b, c;
	char a2, a3;
	puts("Enter x1 y1, x2 y2, x3 y4");
	scanf("%f%f%f%f%f%f", &x1, &y1, &x2, &y2, &x3, &y3);
	// Вычислим коэффициенты A B C, и знаки перед ними
	a = y2-y1; b = x1-x2; c = x2*y1-x1*y2;
	// Проверим, лежат ли значения на одной прямой
	if ((x3-x1)/(x2-x1) == (y3-y1)/(y2-y1)) {
		// Больше ли коэффициент A, чем 0?
		if ((y2-y1) >= 0) {
			if (b >= 0) a2 = '+';
			else {
				a2 = '-';
				b = abs(b);
			}
			if (c >= 0) a3 = '+';
			else {
				a3 = '-';
				c = abs(c);
			}
			printf("%gx%c%gy%c%g=0\n", a, a2, b, a3, c);
		}
		else {
			puts("Coefficient A < 0");
		}
	}
	else {
		printf("Distance to 1 point: %g\nDistance to 2 point: %g\nDistance to 3 point: %g\
			", sqrt(pow(x1, 2) + pow(y1, 2)), sqrt(pow(x2, 2) + pow(y2, 2)),sqrt(pow(x3, 2) + pow(y3, 2)));
	}
}