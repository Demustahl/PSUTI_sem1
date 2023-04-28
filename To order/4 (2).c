#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <string.h>

unsigned int quant = 0;
short answ, f = 0;

typedef struct
{
    char surname[27], sport[28], gender[2];
    int year, height;
} sportsmen;

// Процедуры основного меню
void printSportsmens(); // Вывод всех спортсменов на экран
void scanNewEntry(); // Создание новой записи
void deleteEntry(); // Удаление записи
void changeEntry(); // Изменение записи
void printHeightMen(); // вывести запись о самом высоком спортсмене среди мужчин
void printWomens(); // вывести список спортсменок, выступающих в юниорском отряде (14-17 лет)
void createNewFile(); // Создание нового файла
int checkPresenceFile(); // Проверка наличия файла
void howEntries(); // Подсчет записей в файле
void changeNumberEntries(); // Функция для изменения числа записей в файле

int main()
{
    setlocale(LC_ALL, "Russian");
    if (checkPresenceFile()) {
        howEntries();
    }
    while (1) {
        puts("\n##################################\n\tГЛАВНОЕ МЕНЮ\n\
Введите 1, чтобы вывести список всех спортсменов и их баллы.\n\
Введите 2, чтобы внести запись о новом спортсмене.\n\
Введите 3, чтобы удалить запись об спортсмене\n\
Введите 4, чтобы корректировать данные спортсменов.\n\
Введите 5, чтобы вывести запись о самом высоком спортсмене среди мужчин.\n\
Введите 6, чтобы вывести список спортсменок, выступающих в юниорском отряде (14-17 лет).\n\
Введите 9, чтобы создать новый файл. СТАРЫЙ ФАЙЛ БУДЕТ УДАЛЕН!\n\
Введите 0, чтобы закрыть программу.\n");
        scanf("%hd", &answ);
        getchar();
        switch (answ) {
        case 1:
            if (checkPresenceFile()) {
                if (quant != 0) printSportsmens();
                else puts("\n##################################\nФайл пуст. Выводить нечего.");
            }
            break;
        case 2:
            if (checkPresenceFile()) scanNewEntry();
            break;
        case 3:
            if (checkPresenceFile()) {
                if (quant != 0) deleteEntry();
                else puts("\n##################################\nФайл пуст. Изменять нечего.");
            }
            break;
        case 4:
            if (checkPresenceFile()) {
                if (quant != 0) changeEntry();
                else puts("\n##################################\nФайл пуст. Изменять нечего.");
            }
            break;
        case 5:
            if (checkPresenceFile()) {
                if (quant != 0) printHeightMen();
                else puts("\n##################################\nФайл пуст. Выводить нечего.");
            }
            break;
        case 6:
            if (checkPresenceFile()) {
                if (quant != 0) printWomens();
                else puts("\n##################################\nФайл пуст. Выводить нечего.");
            }
            break;
        case 9:
            puts("\n##################################\nУдаление старого файла и создание нового.\n");
            createNewFile();
            break;
        case 0:
            puts("\n##################################\nЗакрытие программы...\n");
            f = 1;
            break;
        default:
            puts("\n##################################\nВведена неверная команда.\n");
        }
        if (f) break;
    }
    return 0;
}

// Функция для изменения числа записей в файле
void changeNumberEntries() // Принимает новое число, которое нужно записать
{
    FILE* file = fopen("b1.bin", "rb");
    fseek(file, sizeof(unsigned int), SEEK_SET); // перенос вперед на размер int, чтобы считать структуры
    sportsmen* sportsmens = (sportsmen*)malloc((quant) * sizeof(sportsmen));
    fread(sportsmens, sizeof(sportsmen), quant, file);
    fclose(file);
    file = fopen("b1.bin", "wb");
    fwrite(&quant, sizeof(unsigned int), 1, file);
    fwrite(sportsmens, sizeof(sportsmen), quant, file);
    fclose(file);
    free(sportsmens);
}

// Функция для проверки наличия файла
int checkPresenceFile()
{
    FILE* file = fopen("b1.bin", "rb");
    if (file == NULL) {
        puts("\n##################################\nФайл отсутствует. Перед работой с файлом сперва создайте его.\n");
        return 0; // Возвращает 0, если файл отсутствует
    }
    else {
        fclose(file);
        return 1; // Возвращает 1, если файл есть
    }
}

// Функция для определения числа записей из файла
void howEntries()
{
    FILE* file = fopen("b1.bin", "rb");
    fread(&quant, sizeof(unsigned int), 1, file);
    fclose(file);
}

// Функции главного меню
// Функция для создания нового файла
void createNewFile()
{
    quant = 0;
    FILE* file = fopen("b1.bin", "wb");
    fwrite(&quant, sizeof(unsigned int), 1, file);
    fclose(file);
}

// Функция для создания новой записи в файл
void scanNewEntry()
{
    FILE* file = fopen("b1.bin", "ab");
    sportsmen* sportsmens = (sportsmen*)malloc(sizeof(sportsmen));
    do {
        quant++;
        puts("\n##################################\nВведите фамилию спортсмена:");
        scanf("%26s", &sportsmens[0].surname);
        fflush(stdin);
        puts("\nВведите его вид спорта:");
        scanf("%27s", &sportsmens[0].sport);
        fflush(stdin);
        puts("\nВведите его пол, ВВЕДИТЕ w/m:");
        scanf("%1s", &sportsmens[0].gender);
        getchar();
        puts("\nВведите его год рождения:");
        scanf("%d", &sportsmens[0].year);
        getchar();
        puts("\nВведите его рост:");
        scanf("%d", &sportsmens[0].height);
        getchar();
        fwrite(sportsmens, sizeof(sportsmen), 1, file);
        puts("\n##################################\nНовая запись об спортсмене добавлена.\n\
Введите 1, чтобы повторить.\n\
Введите 0, чтобы вернуться в главное меню.\n");
        scanf("%d", &answ);
        getchar();
        switch (answ) {
        case 1:
            continue;
            break;
        case 0:
            puts("\n##################################\nВозвращение в главное меню.\n");
            f = 1;
            break;
        default:
            puts("\n##################################\nВведена неверная команда. Возвращение в главное меню.\n");
            f = 1;
            break;
        }
        if (f) f = 0; break;
    } while (1);
    fclose(file);
    free(sportsmens);
    changeNumberEntries();
}

// Функция для вывода на экран всех записей
void printSportsmens()
{
    FILE* file = fopen("b1.bin", "rb");
    sportsmen* sportsmens = (sportsmen*)malloc((quant) * sizeof(sportsmen));
    fseek(file, sizeof(quant), SEEK_SET); // перенос вперед на размер int, чтобы считать структуры
    fread(sportsmens, sizeof(sportsmen), quant, file);
    puts("\n##################################\n\tСПИСОК СПОРТСМЕНОВ\n");
    puts("ФАМИЛИЯ\t\tВИД СПОРТА\tПОЛ\t\tГОД РОЖДЕНИЯ\t\tРОСТ\n");
    for (int count_array = 0; count_array != quant; count_array++) {
        printf("%s\t\t%s\t\t%s\t\t\t%d\t\t%d\n", \
            sportsmens[count_array].surname, sportsmens[count_array].sport, sportsmens[count_array].gender, sportsmens[count_array].year, sportsmens[count_array].height);
    }
    puts("\nНажмите любую клавишу, чтобы вернуться в главное меню.\n");
    _getch();
    puts("\n##################################\nВозвращение в главное меню.\n");
    fclose(file);
}

// Функция удаления записи об спортсмене
void deleteEntry()
{
    do {
        int have = 0;
        FILE* file = fopen("b1.bin", "rb");
        fseek(file, sizeof(unsigned int), SEEK_SET); // перенос вперед на размер int, чтобы считать структуры
        sportsmen* sportsmens = (sportsmen*)malloc((quant) * sizeof(sportsmen));
        fread(sportsmens, sizeof(sportsmen), quant, file);
        fclose(file);
        char del_surname[27];
        puts("\n##################################\nВведите фамилию спортсмена, запись о котором нужно удалить.\n");
        scanf("%26s", &del_surname);
        fflush(stdin);
        for (int count_sportsmens = 0; count_sportsmens != quant;count_sportsmens++) {
            if (!strcmp(sportsmens[count_sportsmens].surname, del_surname)) have = 1;
        }
        if (have) {
            FILE* file = fopen("b1.bin", "wb");
            quant--;
            fwrite(&quant, sizeof(unsigned int), 1, file);
            for (int count_sportsmens = 0; count_sportsmens != quant + 1; count_sportsmens++) {
                if (strcmp(sportsmens[count_sportsmens].surname, del_surname))
                    fwrite(&sportsmens[count_sportsmens], sizeof(sportsmen), 1, file);
            }
            fclose(file);
            puts("\nЗапись успешно удалена.\n");
        }
        else puts("\nСпортсмен с такой фамилией не найден.\n");
        free(sportsmens);
        puts("\nВведите 1, чтобы повторить.\nВведите 0, чтобы вернуться в главное меню.\n");
        scanf("%hd", &answ);
        getchar();
        switch (answ) {
        case 1:
            continue;
            break;
        case 0:
            puts("\n##################################\nВозвращение в главное меню.\n");
            f = 1;
            break;
        default:
            puts("\n##################################\nВведена неверная команда. Возвращение в главное меню.\n");
            f = 1;
            break;
        }
        if (f) f = 0; break;
    } while (1);
}

// Функция для изменения данных об спортсмене
void changeEntry()
{
    do {
        int have = 0, index;
        FILE* file = fopen("b1.bin", "rb");
        fseek(file, sizeof(unsigned int), SEEK_SET); // перенос вперед на размер int, чтобы считать структуры
        sportsmen* sportsmens = (sportsmen*)malloc((quant) * sizeof(sportsmen));
        fread(sportsmens, sizeof(sportsmen), quant, file);
        fclose(file);
        char change_surname[26];
        puts("\n##################################\nВведите фамилию спортсмена, запись о котором нужно изменить.\n");
        scanf("%19s", &change_surname);
        fflush(stdin);
        for (int count_sportsmens = 0; count_sportsmens != quant;count_sportsmens++) {
            if (!strcmp(sportsmens[count_sportsmens].surname, change_surname)) have = 1, index = count_sportsmens;
        }
        if (have) {
            puts("\nВведите 1, чтобы изменить фамилию.\n\
Введите 2, чтобы изменить вид спорта.\n\
Введите 3, чтобы изменить пол.\n\
Введите 4, чтобы изменить год рождения.\n\
Введите 5, чтобы изменить рост.\n\
Введите 0, чтобы отменить.\n");
            scanf("%hd", &answ);
            getchar();
            switch (answ) {
            case 1:
                puts("\nВведите новую фамилию: \n");
                scanf("%19s", &sportsmens[index].surname);
                fflush(stdin);
                puts("\nФамилия абитуриента успешно изменена.\n");
                break;
            case 2:
                puts("\nВведите новый вид спорта: \n");
                scanf("%19s", &sportsmens[index].sport);
                getchar();
                puts("\nВид спорта спортсмена успешно изменен.\n");
                break;
            case 3:
                puts("\nВведите новый пол: \n");
                scanf("%1s", &sportsmens[index].gender);
                getchar();
                puts("\nПол спортсмена успешно изменен.\n");
                break;
            case 4:
                puts("\nВведите новый год рождения: \n");
                scanf("%d", &sportsmens[index].year);
                getchar();
                puts("\nГод рождения спортсмена успешно изменен.\n");
                break;
            case 5:
                puts("\nВведите новый рост: \n");
                scanf("%d", &sportsmens[index].height);
                getchar();
                puts("\nРост спортсмена успешно изменен.\n");
                break;
            case 0:
                puts("\n##################################\nОтмена.\n");
                break;
            default:
                puts("\n##################################\nВведена неверная команда. Отмена.\n");
            }
        }
        else puts("\nСпортсмен с такой фамилией не найден.\n");
        file = fopen("b1.bin", "wb");
        fwrite(&quant, sizeof(unsigned int), 1, file);
        fwrite(sportsmens, sizeof(sportsmen), quant, file);
        fclose(file);
        free(sportsmens);
        puts("\nВведите 1, чтобы повторить.\n\
Введите 0, чтобы вернуться в главное меню.\n");
        scanf("%hd", &answ);
        getchar();
        switch (answ) {
        case 1:
            continue;
            break;
        case 0:
            puts("\n##################################\nВозвращение в главное меню.\n");
            f = 1;
            break;
        default:
            puts("\n##################################\nВведена неверная команда. Возвращение в главное меню.\n");
            f = 1;
            break;
        }
        if (f) f = 0; break;
    } while (1);
}

// Функция для вывода спортсмена самого высокого роста
void printHeightMen()
{
    short max_height = 0;
    FILE* file = fopen("b1.bin", "rb");
    fseek(file, sizeof(unsigned int), SEEK_SET); // перенос вперед на размер int, чтобы считать структуры
    sportsmen* sportsmens = (sportsmen*)malloc((quant + 1) * sizeof(sportsmen));
    fread(sportsmens, sizeof(sportsmen), quant, file);
    fclose(file);
    for (int count_sportsmens = 0; count_sportsmens != quant; count_sportsmens++) {
        if (sportsmens[count_sportsmens].height > max_height) {
            max_height = sportsmens[count_sportsmens].height;
        }
    }
    puts("\n##################################\n\tСписок спортсменов с наибольшим ростом\n\n");
    puts("ФАМИЛИЯ\t\tВИД СПОРТА\tПОЛ\t\tГОД РОЖДЕНИЯ\t\tРОСТ\n");
    for (int count_array = 0; count_array != quant; count_array++) {
        if (sportsmens[count_array].height == max_height) {
            printf("%s\t\t%s\t\t%s\t\t\t%d\t\t%d\n", \
                sportsmens[count_array].surname, sportsmens[count_array].sport, sportsmens[count_array].gender, sportsmens[count_array].year, sportsmens[count_array].height);
        }
    }
    free(sportsmens);
    puts("\nНажмите любую клавишу, чтобы вернуться в главное меню.\n");
    _getch();
    puts("\n##################################\nВозвращение в главное меню.\n");
}

// Функция для вывода спортсменок юниорского отряда
void printWomens()
{
    short max_height = 0;
    FILE* file = fopen("b1.bin", "rb");
    fseek(file, sizeof(unsigned int), SEEK_SET); // перенос вперед на размер int, чтобы считать структуры
    sportsmen* sportsmens = (sportsmen*)malloc((quant + 1) * sizeof(sportsmen));
    fread(sportsmens, sizeof(sportsmen), quant, file);
    fclose(file);
    puts("\n##################################\n\tСписок спортсменов юниорского отряда\n\n");

    puts("ФАМИЛИЯ\t\tВИД СПОРТА\tПОЛ\t\tГОД РОЖДЕНИЯ\t\tРОСТ\n");
    for (int count_array = 0; count_array != quant; count_array++) {
        if ((!strcmp(sportsmens[count_array].gender, "w")) && (14 <= (2022 - sportsmens[count_array].year)) && ((2022 - sportsmens[count_array].year) <= 17)) {
            printf("%s\t\t%s\t\t%s\t\t\t%d\t\t%d\n", \
                sportsmens[count_array].surname, sportsmens[count_array].sport, sportsmens[count_array].gender, sportsmens[count_array].year, sportsmens[count_array].height);
        }
    }

    free(sportsmens);
    puts("\nНажмите любую клавишу, чтобы вернуться в главное меню.\n");
    _getch();
    puts("\n##################################\nВозвращение в главное меню.\n");
}