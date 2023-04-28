#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <string.h>

const int pass_points_math = 27, pass_points_russ = 36, pass_points_engl = 22, summ_points = 150;
unsigned int quant_students;
short answ, f = 0;

typedef struct
{
    char surname[20];
    int math, russ, engl;
} entrant;

// Процедуры основного меню
void printEntrants();
void scanNewEntry();
void deleteEntry();
void changeEntry();
void printBestEntrans();
void printPercentWorst();
void createNewFile();
// Дополнительные
int checkPresenceFile();
void howEntries();
void changeNumberEntrants();

int main()
{
    setlocale(LC_ALL, "Russian");
    if (checkPresenceFile()) {
        howEntries();
    }
    while (1) {
            puts("\n##################################\n\tГЛАВНОЕ МЕНЮ\n\
Введите 1, чтобы вывести список всех абитуриентов и их баллы.\n\
Введите 2, чтобы внести запись о новом абитуриенте.\n\
Введите 3, чтобы удалить запись об абитуриенте\n\
Введите 4, чтобы корректировать данные абитуриентов.\n\
Введите 5, чтобы вывести список абитуриентов, имеющих наибольшую сумму баллов.\n\
Введите 6, чтобы вывести процент абитуриентов, не прошедших конкурс.\n\
Введите 9, чтобы создать новый файл. СТАРЫЙ ФАЙЛ БУДЕТ УДАЛЕН!\n\
Введите 0, чтобы закрыть программу.\n");
            scanf("%hd", &answ);
            getchar();
            switch (answ) {
            case 1:
                if (checkPresenceFile()) {
                    if (quant_students != 0) printEntrants();
                    else puts("\n##################################\nФайл пуст. Выводить нечего.");
                }
                break;
            case 2:
                if (checkPresenceFile()) scanNewEntry();
                break;
            case 3:
                if (checkPresenceFile()) {
                    if (quant_students != 0) deleteEntry();
                    else puts("\n##################################\nФайл пуст. Изменять нечего.");
                }
                break;
            case 4:
                if (checkPresenceFile()) {
                    if (quant_students != 0) changeEntry();
                    else puts("\n##################################\nФайл пуст. Изменять нечего.");
                }
                break;
            case 5:
                if (checkPresenceFile()) {
                    if (quant_students != 0) printBestEntrans();
                    else puts("\n##################################\nФайл пуст. Выводить нечего.");
                }
                break;
            case 6:
                if (checkPresenceFile()) {
                    if (quant_students != 0) printPercentWorst();
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
void changeNumberEntrants() // Принимает новое число, которое нужно записать
{
    FILE* file = fopen("b1.bin", "rb");
    fseek(file, sizeof(unsigned int), SEEK_SET); // перенос вперед на размер int, чтобы считать структуры
    entrant *entrants = (entrant*)malloc((quant_students) * sizeof(entrant));
    fread(entrants, sizeof(entrant), quant_students, file);
    fclose(file);
    file = fopen("b1.bin", "wb");
    fwrite(&quant_students, sizeof(unsigned int), 1, file);
    fwrite(entrants, sizeof(entrant), quant_students, file);
    fclose(file);
    free(entrants);
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
    fread(&quant_students, sizeof(unsigned int), 1, file);
    fclose(file);
}

// Функции главного меню
// Функция для создания нового файла
void createNewFile() 
{
    quant_students = 0;
    FILE* file = fopen("b1.bin", "wb");
    fwrite(&quant_students, sizeof(unsigned int), 1, file);
    fclose(file);
}

// Функция для создания новой записи в файл
void scanNewEntry() 
{
    FILE* file = fopen("b1.bin", "ab");
    entrant *entrants = (entrant *)malloc(sizeof(entrant));
    do {
        quant_students++;
        puts("\n##################################\nВведите фамилию абитуриента:");
        scanf("%19s", &entrants[0].surname);
        fflush(stdin);
        puts("\nВведите его балл по математике:");
        scanf("%d", &entrants[0].math);
        getchar();
        puts("\nВведите его балл по русскому языку:");
        scanf("%d", &entrants[0].russ);
        getchar();
        puts("\nВведите его балл по английскому языку:");
        scanf("%d", &entrants[0].engl);
        getchar();
        fwrite(entrants, sizeof(entrant), 1, file);
        puts("\n##################################\nНовая запись об абитуриенте добавлена.\n\
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
    free(entrants);
    changeNumberEntrants();
} 

// Функция для вывода на экран всех записей
void printEntrants()
{
    FILE* file = fopen("b1.bin", "rb");
    entrant *entrants = (entrant*)malloc((quant_students) * sizeof(entrant));
    fseek(file, sizeof(quant_students), SEEK_SET); // перенос вперед на размер int, чтобы считать структуры
    fread(entrants, sizeof(entrant), quant_students, file);
    puts("\n##################################\n\tСПИСОК АБИТУРИЕНТОВ\n");
    puts("\tФАМИЛИЯ\t\tМАТЕМАТИКА\tРУССКИЙ ЯЗЫК\t\tАНГЛИЙСКИЙ ЯЗЫК\n");
    for (int count_array = 0; count_array != quant_students; count_array++) {
        printf("%16s\t\t%d\t\t%d\t\t\t%d\n", \
            entrants[count_array].surname, entrants[count_array].math, entrants[count_array].russ, entrants[count_array].engl);
    }
    puts("\nНажмите любую клавишу, чтобы вернуться в главное меню.\n");
    _getch();
    puts("\n##################################\nВозвращение в главное меню.\n");
    fclose(file);
}

// Функция удаления записи об абитуриенте
void deleteEntry()
{
    do {
        int have = 0;
        FILE* file = fopen("b1.bin", "rb");
        fseek(file, sizeof(unsigned int), SEEK_SET); // перенос вперед на размер int, чтобы считать структуры
        entrant* entrants = (entrant*)malloc((quant_students) * sizeof(entrant));
        fread(entrants, sizeof(entrant), quant_students, file);
        fclose(file);
        char del_surname[20];
        puts("\n##################################\nВведите фамилию абитуриента, запись о котором нужно удалить.\n");
        scanf("%19s", &del_surname);
        fflush(stdin);
        for (int count_entrants = 0; count_entrants != quant_students;count_entrants++) {
            if (!strcmp(entrants[count_entrants].surname, del_surname)) have = 1;
        }
        if (have) {
            FILE* file = fopen("b1.bin", "wb");
            quant_students--;
            fwrite(&quant_students, sizeof(unsigned int), 1, file);
            for (int count_entrants = 0; count_entrants != quant_students + 1; count_entrants++) {
                if (strcmp(entrants[count_entrants].surname, del_surname))
                    fwrite(&entrants[count_entrants], sizeof(entrant), 1, file);
            }
            fclose(file);
            puts("\nЗапись успешно удалена.\n");
        }
        else puts("\nАбитуриент с такой фамилией не найден.\n");
        free(entrants);
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

// Функция для изменения данных об абитуриенте
void changeEntry()
{
    do {
        int have = 0, index;
        FILE* file = fopen("b1.bin", "rb");
        fseek(file, sizeof(unsigned int), SEEK_SET); // перенос вперед на размер int, чтобы считать структуры
        entrant* entrants = (entrant*)malloc((quant_students) * sizeof(entrant));
        fread(entrants, sizeof(entrant), quant_students, file);
        fclose(file);
        char change_surname[20];
        puts("\n##################################\nВведите фамилию абитуриента, запись о котором нужно изменить.\n");
        scanf("%19s", &change_surname);
        fflush(stdin);
        for (int count_entrants = 0; count_entrants != quant_students;count_entrants++) {
            if (!strcmp(entrants[count_entrants].surname, change_surname)) have = 1, index = count_entrants;
        }
        if (have) {
            puts("\nВведите 1, чтобы изменить фамилию.\n\
Введите 2, чтобы изменить балл по математике.\n\
Введите 3, чтобы изменить балл по русскому языку.\n\
Введите 4, чтобы изменить балл по английскому языку.\n\
Введите 0, чтобы отменить.\n");
            scanf("%hd", &answ);
            getchar();
            switch (answ) {
            case 1:
                puts("\nВведите новую фамилию: \n");
                scanf("%19s", &entrants[index].surname);
                fflush(stdin);
                puts("\nФамилия абитуриента успешно изменена.\n");
                break;
            case 2:
                puts("\nВведите новый балл: \n");
                scanf("%d", &entrants[index].math);
                getchar();
                puts("\nБалл по математике абитуриента успешно изменен.\n");
                break;
            case 3:
                puts("\nВведите новый балл: \n");
                scanf("%d", &entrants[index].russ);
                getchar();
                puts("\nБалл по русскому языку абитуриента успешно изменен.\n");
                break;
            case 4:
                puts("\nВведите новый балл: \n");
                scanf("%d", &entrants[index].engl);
                getchar();
                puts("\nБалл по английскому языку абитуриента успешно изменен.\n");
                break;
            case 0:
                puts("\n##################################\nОтмена.\n");
                break;
            default:
                puts("\n##################################\nВведена неверная команда. Отмена.\n");
            }
        }
        else puts("\nАбитуриент с такой фамилией не найден.\n");
        file = fopen("b1.bin", "wb");
        fwrite(&quant_students, sizeof(unsigned int), 1, file);
        fwrite(entrants, sizeof(entrant), quant_students, file);
        fclose(file);
        free(entrants);
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

// Функция для вывода абитуриентов с наибольшим количеством баллов
void printBestEntrans()
{
    short max_summ = 0;
    FILE* file = fopen("b1.bin", "rb");
    fseek(file, sizeof(unsigned int), SEEK_SET); // перенос вперед на размер int, чтобы считать структуры
    entrant *entrants = (entrant*)malloc((quant_students + 1) * sizeof(entrant));
    fread(entrants, sizeof(entrant), quant_students, file);
    fclose(file);
    for (int count_entrants = 0; count_entrants != quant_students; count_entrants++) {
        if (entrants[count_entrants].math + entrants[count_entrants].russ + entrants[count_entrants].engl > max_summ) {
            max_summ = entrants[count_entrants].math + entrants[count_entrants].russ + entrants[count_entrants].engl;
        }
    }
    puts("\n##################################\n\tСписок абитуриентов с наибольшим количеством баллов\n\n\
Фамилия\t\t\tБалл по мат.\t\tБалл по рус.\t\tБалл по англ.\t\tСумм. балл\n");
    for (int count_entrants = 0; count_entrants != quant_students; count_entrants++) {
        if (entrants[count_entrants].math + entrants[count_entrants].russ + entrants[count_entrants].engl == max_summ)
            printf("%s\t\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", entrants[count_entrants].surname,\
                entrants[count_entrants].math, entrants[count_entrants].russ, entrants[count_entrants].engl, max_summ);
    }
    free(entrants);
    puts("\nНажмите любую клавишу, чтобы вернуться в главное меню.\n");
    _getch();
    puts("\n##################################\nВозвращение в главное меню.\n");
}

// Функция для вывода процента абитуриентов, не прошедших конкурс
void printPercentWorst()
{
    unsigned int how_many = 0;
    FILE* file = fopen("b1.bin", "rb");
    fseek(file, sizeof(unsigned int), SEEK_SET); // перенос вперед на размер int, чтобы считать структуры
    entrant *entrants = (entrant*)malloc((quant_students + 1) * sizeof(entrant));
    fread(entrants, sizeof(entrant), quant_students, file);
    fclose(file);
    printf("\n##################################\nМин. балл по мат: %hd. Мин. балл по рус: %hd.\
 Мин. балл по англ: %hd. Мин. сум. балл: %hd\n\
\tСписок абитуриентов с наибольшим количеством баллов\n\n\
Фамилия\t\t\tБалл по мат.\t\tБалл по рус.\t\tБалл по англ.\t\tСум. балл\n",\
    pass_points_math, pass_points_russ, pass_points_engl, summ_points);
    for (int count_entrants = 0; count_entrants != quant_students; count_entrants++) {
        if ((entrants[count_entrants].math < pass_points_math) || (entrants[count_entrants].russ < pass_points_russ)\
            || (entrants[count_entrants].engl < pass_points_engl)\
            || (entrants[count_entrants].math + entrants[count_entrants].russ + entrants[count_entrants].engl < summ_points)) {
            how_many++;
            printf("%s\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", entrants[count_entrants].surname,\
                entrants[count_entrants].math, entrants[count_entrants].russ, entrants[count_entrants].engl, \
                (entrants[count_entrants].math + entrants[count_entrants].russ + entrants[count_entrants].engl));
        }
    }
    printf("\nПроцент абитуриентов, не прошедших конкурс: %.0f%%\n", ((float)how_many / (float)quant_students) * 100.0);
    free(entrants);
    puts("\nНажмите любую клавишу, чтобы вернуться в главное меню.\n");
    _getch();
    puts("\n##################################\nВозвращение в главное меню.\n");
}