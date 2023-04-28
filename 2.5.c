#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	long long sum = 0;
	int x = 0, y = 0;
	do {
		puts("Enter two natural numbers: ");
		scanf("%d %d", &x, &y);
	} while ((x <= 0) || (y <= 0));
	while (x <= y) {
		if (x % 2 == 0) sum += pow(x, 3);
		x++;
	}
	printf("The sum of cubes of all even numbers lying in the range [X, Y]: %d", sum);
}