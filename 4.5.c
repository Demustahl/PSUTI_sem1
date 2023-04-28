#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main()
{
	int stool[6][6][6];
	// Нарисуем табурет
	for (int i = 0; i != 6; i++) {
		for (int ii = 0; ii != 6; ii++) {
			for (int iii = 0; iii != 6; iii++) {
				if (i == 0) {
					stool[i][ii][iii] = 1;
				}
				else if ((i == 1) || (i == 4)) {
					if (((ii == 0) || (ii == 5)) || ((iii == 0) || (iii == 5))) {
						stool[i][ii][iii] = 1;
					}
					else if ((ii == 1) || (ii == 4)) {
						if ((iii == 0) || (iii == 1) || (iii == 4) || (iii == 5)) {
							stool[i][ii][iii] = 1;
						}
						else {
							stool[i][ii][iii] = 0;
						}
					}
					else {
						stool[i][ii][iii] = 0;
					}
				}
				else if ((i == 2) || (i == 3) || (i == 5)) {
					if (((iii == 2) || (iii == 3)) || ((ii == 2) || (ii == 3))) {
						stool[i][ii][iii] = 0;
					}
					else {
						stool[i][ii][iii] = 1;
					}
				}
			}
		}
	}
	// Выведем табурет
	for (int i = 0; i != 6; i++) {
		for (int ii = 0; ii != 6; ii++) {
			puts(" ");
			for (int iii = 0; iii != 6; iii++) {
				printf("%d", stool[i][ii][iii]);
			}
		}
		puts(" ");
	}
	return 0;
}