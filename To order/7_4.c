#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SizeName 20

struct DATA
{
	char Latiname[SizeName]; //обозначение
	char name[SizeName]; //название
	float mass; //атомная масса
	int charge; //заряд
};

int number_records_in_file(char* FileName) //Определение количества записей
{
	int size = 0;
	FILE* f = fopen(FileName, "rb"); //Открываем файл
	if (f == NULL) //Проверка наличия файла 	
		printf("\nОшибка открытия файла.\n");
	else
	{
		fseek(f, 0, SEEK_END);
		size = ftell(f) / sizeof(struct DATA);
		fclose(f);
	}
	return size;
}

void print_mask()
{
	printf("|%5s", "#");
	printf("|%15s", "Обозначение");
	printf("|%15s", "Название");
	printf("|%15s", "Атомная масса");
	printf("|%15s|\n", "Заряд");
}

void print_item(struct DATA item, int k)
{
	//выводим на экран
	printf("|%5i", k);
	printf("|%15s", item.Latiname);
	printf("|%15s", item.name);
	printf("|%15.2f", item.mass);
	printf("|%15d", item.charge);
	puts("");
}

void output_to_the_screen(char* FileName) //вывод на экран
{
	if (number_records_in_file(FileName) > 0)
	{
		FILE* f = fopen(FileName, "rb");
		struct DATA item;
		print_mask();
		int i = 0;
		while (fread(&item, sizeof(struct DATA), 1, f) > 0)
		{
			//выводим на экран
			i++;
			print_item(item, i);
		}
		fclose(f); //Закрываем файл
		printf("\nВывод завершен.\n");
	}
	else
		printf("\nНет данных для вывода.\n");
}

void insert_data_to_the_file(char* FileName) //добавление данных
{
	FILE* f = fopen(FileName, "a"); //открываем файл
	if (f == NULL) //Проверка наличия файла 	
		printf("\nОшибка открытия файла.\n");
	else
	{
		struct DATA item;
		fflush(stdin); //очищаем буфер ввода
		printf("Введите латинское обозначение элемента: ");
		scanf("%s", &item.Latiname);
		printf("Введите Название химического элемента: ");
		scanf("%s", &item.name);
		printf("Введите атомную массу: ");
		scanf("%f", &item.mass);
		printf("Введите заряд ядра: ");
		scanf("%d", &item.charge);
		fwrite(&item, sizeof(struct DATA), 1, f);
		fclose(f); //Закрываем файл
		printf("\nДанные добавлены.\n");
	}
}

void del_data_to_the_file(char* FileName) //удаление данных
{
	int n = number_records_in_file(FileName);
	if (n > 0)
	{
		FILE* f = fopen(FileName, "rb"); //открываем файл
		if (f == NULL) //Проверка наличия файла 	
			printf("\nОшибка открытия файла.\n");
		else
		{
			FILE* ou = fopen("temp.txt", "wb"); //создаём временный файл
			if (f == NULL) //Проверка наличия файла 	
				printf("\nНе удалось создать файл.\n");
			else
			{
				print_mask();
				int i;
				struct DATA item;
				for (i = 0; i < n; i++)
				{
					fread(&item, sizeof(struct DATA), 1, f);
					print_item(item, i + 1);
				}

				int key;
				printf("Введите номер удаляемой записи: ");
				scanf("%i", &key);

				fseek(f, 0, SEEK_SET);
				for (i = 0; i < n; i++)
				{
					fread(&item, sizeof(struct DATA), 1, f);
					if (i != (key - 1))
					{
						fwrite(&item, sizeof(struct DATA), 1, ou);
					}
				}
				fclose(f); //Закрываем файл
				fclose(ou); //Закрываем файл
				remove(FileName);
				rename("temp.txt", FileName);
				printf("\nЗапись удалена.\n");
			}

		}
	}
	else
		printf("\nНет данных для удаления.\n");
}

void edit_data_to_the_file(char* FileName) //корректировка данных
{
	int n = number_records_in_file(FileName);
	if (n > 0)
	{
		FILE* f = fopen(FileName, "rb+"); //открываем файл
		if (f == NULL) //Проверка наличия файла 	
			printf("\nОшибка открытия файла.\n");
		else
		{
			print_mask();
			int i;
			struct DATA item;
			for (i = 0; i < n; i++)
			{
				fread(&item, sizeof(struct DATA), 1, f);
				print_item(item, i + 1);
			}

			int key;
			printf("Введите номер корректируемой записи: ");
			scanf("%i", &key);

			fflush(stdin); //очищаем буфер ввода
			printf("Введите латинское обозначение элемента: ");
			scanf("%s", &item.Latiname);
			printf("Введите химического элемента: ");
			scanf("%s", &item.name);
			printf("Введите атомную массу: ");
			scanf("%f", &item.mass);
			printf("Введите заряд ядра: ");
			scanf("%d", &item.charge);

			fseek(f, (key - 1) * sizeof(struct DATA), SEEK_SET);
			fwrite(&item, sizeof(struct DATA), 1, f);
			fclose(f); //Закрываем файл

			printf("\nЗапись изменена.\n");
		}
	}
	else
		printf("\nНет данных для редактирования.\n");
}

void seach(char* FileName) //поиск по возрасту и сумме
{
	int n = number_records_in_file(FileName);
	if (n > 0)
	{
		FILE* f = fopen(FileName, "rb"); //открываем файл
		if (f == NULL) //Проверка наличия файла 	
			printf("\nОшибка открытия файла.\n");
		else
		{
			int i, k = 0;

			char nazvan[3];
			printf("Введите латинское обозачение требуемого химического элемента: ");
			scanf("%s", &nazvan);
			print_mask();
			struct DATA item;
			for (i = 0; i < n; i++)
			{
				fread(&item, sizeof(struct DATA), 1, f);
				if (strcmp(nazvan, item.Latiname) == 0)
				{
					print_item(item, i + 1);
					k++;
				}
			}
			fclose(f);
			if (k == 0)
				printf("\n Химических элементов с таким названием не найдено.\n");
		}
	}
	else
		printf("\nНет данных для поиска.\n");
}

void seach_max(char* FileName) //поиск элемента с наибольшей массой
{
	int n = number_records_in_file(FileName);
	if (n > 0)
	{
		FILE* f = fopen(FileName, "rb"); //открываем файл
		if (f == NULL) //Проверка наличия файла 	
			printf("\nОшибка открытия файла.\n");
		else
		{
			int i, k = 0;
			print_mask();
			struct DATA item_max;
			item_max.mass = 0;
			struct DATA item;
			struct DATA need_item;
			for (i = 0; i < n; i++)
			{
				fread(&item, sizeof(struct DATA), 1, f);
				if (item.mass > item_max.mass)
				{
					item_max.mass = item.mass;
					need_item = item;
					k++;
				}
				if (i == n - 1) {
					print_item(need_item, i + 1);
				}
			}
			fclose(f);
			if (k == 0)
				printf("\n Элементов с такими параметрами не найдено.\n");
		}
	}
	else
		printf("\nНет данных для поиска.\n");
}

int main() {
	system("chcp 1251 > nul");
	char* FileName = "test.txt";
	char* Result = "result.txt";
	FILE* f;
	if ((f = fopen(FileName, "r")) == NULL) //проверка наличия файла 
		f = fopen(FileName, "w"); //если ошибка открытия, создаём файл
	fclose(f);
	char key; //номер пункта меню
	do
	{
		printf("Введите номер пункта меню:\n");
		printf("1: Ввод данных в файл;\n");
		printf("2: Удаление записей;\n");
		printf("3: Вывод на экран;\n");
		printf("4: Редактирование записей;\n");
		printf("5: Поиск элемента по его обозначению;\n");
		printf("6: Элемент с наибольшей атомной массой;\n");
		printf("0: Выход.\n");
		do
		{
			scanf("%c", &key); //считываем из буфера ввода клавиатуры данные
		} while (key < '0' || key > '6'); //проверка корректности введенных данных
		switch (key) //анализ введенных данных
		{
		case '1': printf("\n"); insert_data_to_the_file(FileName); printf("\n"); break;
		case '2': printf("\n"); del_data_to_the_file(FileName); printf("\n"); break;
		case '3': printf("\n"); output_to_the_screen(FileName); printf("\n"); break;
		case '4': printf("\n"); edit_data_to_the_file(FileName); printf("\n"); break;
		case '5': printf("\n"); seach(FileName); printf("\n"); break;
		case '6': printf("\n"); seach_max(FileName); printf("\n"); break;
		}
		fflush(stdin);
	} while (key != '0'); //выполняется пока не введут 0     	
}
