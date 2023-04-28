#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// Фун. заполнения двумерного массива пользователем
void filling_array_user_int(int ** M, int len_1, int len_2)
{
	for (int i = 0; i != len_1; i++) {
		printf("Enter line %d:\n", i + 1);
		for (int ii = 0; ii != len_2; ii++) {
			scanf("%d", &M[i][ii]);
		}
	}
}

// Фун. вывода двумерного массива типа int
void print_array_int(int ** M, int len_1, int len_2)
{
	puts(" ");
	for (int i = 0; i != len_1; i++) {
		printf("line %d:", i + 1);
		for (int ii = 0; ii != len_2; ii++) {
			printf(" %5d", M[i][ii]);
		}
		puts(" ");
	}
}

int main()
{
	int s_p_1, s_p_2, number_pairs = 0;
	int **p;
	printf("Enter numbers of lines: ");
	scanf("%d", &s_p_1); 
	printf("Enter numbers of columns: ");
	scanf("%d", &s_p_2);
	p = (int **)malloc(s_p_1 * sizeof(int));
	for (int i = 0; i < s_p_1; i++) {
    	p[i] = (int *)malloc(s_p_2 * sizeof(int));
	}
	// Пользователь заполняет массив, затем выводим его
	filling_array_user_int(p, s_p_1, s_p_2);
	print_array_int(p, s_p_1, s_p_2);
	// Создаем много условий, чтобы не  проверять лишние значения
	for (int i = 0; i != s_p_1; i++) {
		for (int ii = 0; ii != s_p_2; ii++){
				if ((i != s_p_1 - 1) && (ii != s_p_2 - 1)) {
					if ((p[i][ii] == p[i][ii + 1]) && (p[i][ii] == p[i + 1][ii])) {
						number_pairs += 2;
					}
					else if ((p[i][ii] == p[i][ii + 1]) || (p[i][ii] == p[i + 1][ii])) {
						number_pairs++;
					}
				}
				else if ((i == s_p_1 - 1) && (ii != s_p_2 - 1)) {
					if (p[i][ii] == p[i][ii + 1]) {
						number_pairs++;
					}
				}
				else if ((i != s_p_1 - 1) && (ii == s_p_2 - 1)) {
					if (p[i][ii] == p[i + 1][ii]) {
						number_pairs++;
					}
				}
			}
	}
	printf("The number of pairs of identical numbers: %d", number_pairs);
	for (int i = 0; i < s_p_1; i++) {
    	free(p[i]);
	}
	free(p);
	return 0;
}