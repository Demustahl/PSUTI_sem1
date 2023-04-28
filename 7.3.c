#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#define QUANT 100

int main()
{
	// Записываем вещественные числа в бинарный файл
	FILE * file_b;
	file_b = fopen("b1.bin", "wb");
	int i_ar;
	float nums[QUANT], num, mean, sum = 0.0;
	// Выведем изначальные цифры на экран и запишем их в массив
	for (i_ar = 0; i_ar != QUANT; i_ar++) {
		num = 50.0 / ((float)(10 + rand() % 30));
		nums[i_ar] = num;
		printf("%.2f  ", num);
	}
	fclose(file_b);
	// Затем читаем вещ. числа из файла и записываем их в массив
	file_b = fopen("b1.bin", "rb");
	fread(&nums, sizeof(float), QUANT, file_b);
	// Пройдемся по массиву, складывая числа
	for (i_ar = 0; i_ar != QUANT; i_ar++) {
		sum += nums[i_ar];
	}
	// Пройдемся по массиву заново, вычитая среднее арифметическое
	mean = sum / (float)QUANT;
	for (i_ar = 0; i_ar != QUANT; i_ar++) {
		nums[i_ar] -= mean;
	}
	fclose(file_b);
	// Запишем результат в файл
	file_b = fopen("b1.bin", "wb");
	fwrite(&nums, sizeof(float), QUANT, file_b);
	fclose(file_b);
	// Выведем результат на экран
	file_b = fopen("b1.bin", "rb");
	fread(&nums, sizeof(float), QUANT, file_b);
	printf("\n\nArithmetic mean: %.2f\n\n", mean);
	for (i_ar = 0; i_ar < QUANT; i_ar++) {
		printf("%.2f  ", nums[i_ar]);
	}
	fclose(file_b);
	getch();
	return 0;
}