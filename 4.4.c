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
	int s_p_1, s_p_2, z, x_max, x_min;
	float result;
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
	// Ищем максимальное и минимальное значения
	x_max = p[0][0]; x_min = p[0][0];
	for (int i = 0; i != s_p_1; i++) {
		for (int ii = 0; ii != s_p_2; ii++){
			if (p[i][ii] > x_max) x_max = p[i][ii];
			if (p[i][ii] < x_min) x_min = p[i][ii];
		}
	}
	printf("\nX_max = %d; x_min = %d\n", x_max, x_min);
	result = x_min/(float)(x_max + x_min);
	printf("Z = %f", result);
	for (int i = 0; i < s_p_1; i++) {
    	free(p[i]);
	}
	free(p);
	return 0;
}