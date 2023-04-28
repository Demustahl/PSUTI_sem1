#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

int main()
{
	FILE * file;
	file = fopen("f2.txt", "r");
	char numbers[1000], ch;
  	int nums = 0, i_numbers = 0;
	do {
		ch = getc(file);
		if ((nums + 1) % 5 == 0) {
			nums++;
			do {
				ch = getc(file);
			} while ((ch != ' ') && (ch != '\n'));
			ch = getc(file);
		}
		if (ch == '\n') ch = ' ';
		if (((ch == ' ') || (ch == '\n')) && (nums != 0)) {
			numbers[i_numbers] = ch;
			i_numbers++;
		}
		else if ((ch != ' ') && (ch != '\n')) {
			nums++;
			do {
				numbers[i_numbers] = ch;
				i_numbers++;
				ch = getc(file);
			} while ((ch != ' ') && (ch != '\n') && (ch != EOF));
			if (ch == '\n') ch = ' ';
			numbers[i_numbers] = ch;
			i_numbers++;
		}
	} while (ch != EOF);
	numbers[i_numbers - 1] = '\0';
	puts(numbers);
	fclose(file);
	// Перезапись файла
	file = fopen("f1.txt", "w");
	for (i_numbers = 0, nums = 0;;i_numbers++) {
		ch = numbers[i_numbers];
		if ((ch == EOF) || (ch == '\0')) break;
		if (ch == ' ') {
			nums++;
			if (nums % 5 == 0) ch = '\n';
		}
		fprintf(file, "%c", ch);
	}
	fclose(file);
	getch();
	return 0;
}