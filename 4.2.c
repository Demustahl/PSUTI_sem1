#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// Фун. заполнения массива пользователем
void filling_array_user_int(int * M, int len)
{
	for (int i = 0; i != len; i++) {
		scanf("%d", &M[i]);
	}
}

// Фун. вывода массива типа int
void print_array_int(int * M, int len)
{
	puts(" ");
	for (int i = 0; i != len; i++) {
		printf("%d ", M[i]);
	}
}

int main()
{
	int size_M, number_zeros = 0, ind_M = 0, ind_side_M = 0;
	int *p_M, *p_side_M;
	printf("Enter size_M array M: ");
	scanf("%d", &size_M);
	p_M = (int *)malloc(size_M * sizeof(int));
	// Пользователь заполняет массив
	filling_array_user_int(p_M, size_M);
	// Выводим массив
	print_array_int(p_M, size_M);
	// Посчитаем нули в массиве M
	for (int i = 0; i != size_M; i++) {
		if (p_M[i] == 0) {
			number_zeros++;
		}
	}
	// Теперь в побочный массив запишем старый без нулей и запишем его в старый
	p_side_M = (int *)malloc(size_M - number_zeros);
	while (ind_side_M != size_M - number_zeros) {
		if (p_M[ind_M] != 0) {
			p_side_M[ind_side_M] = p_M[ind_M];
			ind_M++; ind_side_M++;
		}
		else {
			ind_M++;
		}
	}
	p_M = p_side_M;
	// Выведем измененный массив массив 
	print_array_int(p_M, size_M - number_zeros);
	free(p_M);
	free(p_side_M);
	return 0;
}