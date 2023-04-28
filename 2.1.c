/*
Вариант 17
*/
#include <stdio.h>
#include <stdlib.h>

int main(){
	float n, m, res;
	puts("Enter N and M numbers:  ");
	scanf("%f%f", &n, &m);
	// Тернарный оператор
	res = n >= 0 ? n - 4 : (((m < 0) && (n < 0)) ? ((m+n)/(m*n)) : m + 5);
	printf("Result: %f", res);
}