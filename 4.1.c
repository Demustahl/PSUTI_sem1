#include <stdio.h>
#include <stdlib.h>

int size_int = sizeof(int);

// Фун. заполнения массива случайными цифрами от 1 до 100
void filling_array_int_1to100(int M[], int len)
{
	for (int i = 0; i != len; i++) {
		M[i] = rand() % 101;
	}
}

// Фун. вывода массива типа int
void print_array_int(int M[], int len)
{
	for (int i = 0; i != len; i++) {
		printf("%d ", M[i]);
	}
}

// Фун. упорядочивания массива по убыванию
void ordering_descending(int M[], int len) 
{
	int ind = 1, replace;
	while (ind == 1) {
		ind = 0;
		for (int i = len - 1; i != 0; i--) {
			if (M[i] > M[i - 1]) {
				replace = M[i - 1];
				M[i - 1] = M[i];
				M[i] = replace;
				ind = 1;
			}
		}
	}
}

int main()
{
	const int size_A= 12, size_B= 20;
	int A[size_A], B[size_B], AandB[size_A + size_B], ind_AandB = 0;
	// Заполним массивы A и B случайными числами от 1 до 100;
	filling_array_int_1to100(A, sizeof(A)/size_int);
	filling_array_int_1to100(B, sizeof(B)/size_int);
	// Выведем на экран оба массива
	puts("\nArray A:");
	print_array_int(A, sizeof(A)/size_int);
	puts("\nArray B:");
	print_array_int(B, sizeof(B)/size_int);
	// Упорядочиваем по убыванию массивы
	ordering_descending(A, sizeof(A)/size_int);
	ordering_descending(B, sizeof(B)/size_int);
	// Выведем на экран оба массива
	puts("\nArray A:");
	print_array_int(A, sizeof(A)/size_int);
	puts("\nArray B:");
	print_array_int(B, sizeof(B)/size_int);
	// Заполним массив AandB числами из массивов A и B
	for (int ind = 0; ind != size_A; ind++, ind_AandB++) {
		AandB[ind_AandB] = A[ind];
	}
	for (int ind = 0; ind != size_B; ind++, ind_AandB++) {
		AandB[ind_AandB] = B[ind];
	}
	// Выведем на экран массив AandB
	puts("\nArray AandB:");
	print_array_int(AandB, sizeof(AandB)/size_int);
	// Упорядочим массив AandB по убыванию
	ordering_descending(AandB, sizeof(AandB)/size_int);
	// Выведем на экран массив AandB
	puts("\nArray AandB:");
	print_array_int(AandB, sizeof(AandB)/size_int);
	return 0;
}