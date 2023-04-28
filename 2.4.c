#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	float f;
	for (int c = 0; c != 101; c++) {
		f = (9*(float)c)/5+32;
		printf("%d C --> %g F\n", c, f);
	}
}