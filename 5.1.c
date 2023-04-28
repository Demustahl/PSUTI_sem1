#include <stdio.h>
#include <stdlib.h>

int s_p_1 = 6, s_p_2 = 7;

// Фун. заполнения двумерного массива случайными числами от 1 до 100
void filling_array_user_int(int M[s_p_1][s_p_2])
{
	for (int i = 0; i != s_p_1; i++) {
		for (int ii = 0; ii != s_p_2; ii++) {
			M[i][ii] = rand() % 101;
		}
	}
}

// Фун. вывода двумерного массива типа int
void print_array_int(int M[s_p_1][s_p_2])
{
	puts(" ");
	for (int i = 0; i != s_p_1; i++) {
		printf("line %d:", i + 1);
		for (int ii = 0; ii != s_p_2; ii++) {
			printf(" %5d", M[i][ii]);
		}
		puts(" ");
	}
}

// Фун. упорядочивания массива по убыванию или возрастанию
// Если второй передаваемый аргумент равен 0, то сортировать в порядке убывания
void ordering_descending(int M[s_p_2], int direction) 
{
	int ind = 1, replace;
	if (direction == 0) {
		while (ind == 1) {
			ind = 0;
			for (int i = s_p_2 - 1; i != 0; i--) {
				if (M[i] > M[i - 1]) {
					replace = M[i - 1];
					M[i - 1] = M[i];
					M[i] = replace;
					ind = 1;
				}
			}
		}
	}
	else {
		while (ind == 1) {
			ind = 0;
			for (int i = 0; i != s_p_2 - 1; i++) {
				if (M[i] > M[i + 1]) {
					replace = M[i + 1];
					M[i + 1] = M[i];
					M[i] = replace;
					ind = 1;
				}
			}
		}
	}
}

int main()
{
	int M[s_p_1][s_p_2];
	filling_array_user_int(M);
	print_array_int(M);
	for (int i = 0; i != s_p_1; i++) {
		if ((i + 1) % 2 ) {
			ordering_descending(M[i], 0);
		}
		else {
			ordering_descending(M[i], 1);
		}
	}
	print_array_int(M);
	return 0;
}