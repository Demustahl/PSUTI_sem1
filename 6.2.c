#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) 
{
	char str1[101];
	char str2[101];
	char big_word[101];
	char* begin = str1;
	char* end;
	char* m3;
	int len = 0, ii = 0;
	puts("Enter a sentence:");
	fgets(str1, 100, stdin);
	end = (char *)(begin + strlen(str1) - 1);
	for (int i = 0; &str1[i] != end + 1; i++) {
		if (str1[i] != ' ') {
			str2[ii] = str1[i];
			ii++;
		}
		else {
			if (ii > len) {
				len = ii;
				for (int ci = 0; ci < len; ci++) {
					big_word[ci] = str2[ci];
				}
			}
			ii = 0;
		}
	}
	for (int i = 0; i != len; i++) {
		printf("%c", big_word[i]);
	}
}