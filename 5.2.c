#include <stdio.h>
#include <stdlib.h>

// Фун. заполнения двумерного массива случайными числами от 1 до 100
void filling_array_random_int(int *M, int s1, int s2)
{
	for (int i = 0; i != s1; i++) {
		printf("Enter line %d (%d numbers):\n", i + 1, s2);
		for (int ii = 0; ii != s2; ii++) {
			scanf("%d", &M[i*s2 + ii]);
		}
	}
}

// Фун. вывода двумерного массива типа int
void print_array_int(int *M, int s1, int s2)
{
	puts(" ");
	for (int i = 0; i != s1; i++) {
		printf("line %d:", i + 1);
		for (int ii = 0; ii != s2; ii++) {
			printf(" %5d", M[i*s2 + ii]);
		}
		puts(" ");
	}
}

// Фун. для анализа столбцов матрицы
void checking_columns(int *M, int s1, int s2)
{
	int quantity = 0, flag;
	for (int ii = 0; ii != s2; ii++) {
		flag = 0;
		for (int i = 0; i != s1; i++) {
			if (M[i*s2 + ii] < 0) flag++;
		}
		if (flag >= 2) printf("Column %d\n", ii + 1);
	}
}

int main()
{
	int m = 3, n = 4;
	int A[m][n], B[n][m];
	puts("Array A:");
	filling_array_random_int(&A[0][0], m, n);
	puts("Array B:");
	filling_array_random_int(&B[0][0], n, m);
	puts("Array A:");
	print_array_int(&A[0][0], m, n);
	puts("Array B:");
	print_array_int(&B[0][0], n, m);
	puts("Array A:");
	checking_columns(&A[0][0], m, n);
	puts("Array B:");
	checking_columns(&B[0][0], n, m);
	return 0;
}

// Значения для проверки -2 4 5 -1 -1 2 0 1 -8 4 -12 -9 5 6 1 -2 -2 -2 -1 1 -1 1 2 3