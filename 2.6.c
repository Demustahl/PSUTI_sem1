#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	int N, Ns, Nss, two = 1;
	puts("Enter number: ");
	scanf("%d", &N);
	Ns = N;
	while (Ns != 0) {
		Nss = Ns % 10;
		if ((Nss != 0) && (Nss != 1)) {
			two = 0;
			break;
		}
		Ns = Ns / 10;
	}
	if (two == 1) printf("The number %d is binary!\n", N);
	else printf("The number %d is not binary(\n", N);
	return 0;
}