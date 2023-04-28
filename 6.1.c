#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) 
{
	int num, len;
	char swap;
	char str1[101];
	puts("Enter a sentence:");
	fgets(str1, 100, stdin);
	puts("How many characters to swap:");
	scanf("%d", &num);
	len = strlen(str1) - 1;
	if (num > len / 2) num = len / 2;
	for (int i = 0; i < num; i++) {
		swap = str1[i];
		str1[i] = str1[len - i - 1];
		str1[len - i - 1] = swap;
	}
	puts("Result:");
	puts(str1);
}