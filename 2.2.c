/*
Вариант 17
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	float x, y, res;
	short ok = 1;
//	bool ok = true;
	while (ok == 1) {
		puts("Enter X and Y numbers:  ");
		scanf("%f%f", &x, &y);
		if ((y != 0) && (log(fabs(4*pow(y, 3))) != 0)) break;
		puts("The arguments do not belong to the scope of the function definition!");
	}
	res =(sin(x)*cos(y)-(sin(x/y)/cos(x/y)))/(log(fabs(4*pow(y, 3))));
	printf("Result: %f", res);
}