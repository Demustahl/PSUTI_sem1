#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <time.h>

// Структура записи
typedef struct {
    int id;
    char animal[32];
    char area[32];
    int money;
} record;

// Создание случайных записей в файле
void createRecords(int count, char* filename) {
    FILE* file = fopen(filename, "wb");
    char* animals_arctic[25] = {"polarbear", "tundrawolf", "polarfox", "walrus", "whale", "seal", "penguin", "goose", "seagull", "lemming", "wolf", "northerndeer", "belukha", "muskox", "killerwhale", "ermine", "wolverine", "lemming", "snowsheep", "polarcod", "blackbarracks", "loon", "kyra", "whiteowl", "arcticcyanea"};
    char* animals_forests[30] = { "deer", "bear", "klest", "woodpecker", "squirrel", "wolf", "hog", "moose", "marten", "badger", "hare", "rabbit", "fox", "lynx", "leopard", "tiger" , "bluethroat" , "nightingale" , "finch" , "blackgrouse" , "oriole" , "raven" , "bison" , "roe deer" , "pig" , "bison" , "hedgehog" , "ferret" , "marten" , "mole" };
    char* animals_steppes[27] = { "chipmunk", "gopher", "jerboa", "saiga", "steppenwolf", "fox", "groundhog", "hawk", "eagle", "wildhorse", "antelope", "hamster", "kestrel", "steppeviper", "weasel", "jaguar" , "battleship" , "anteater" , "capybara" , "kulan" , "baibak" , "skid" , "kobchik" , "crane" , "bustard" , "vole" , "groundhog" };
    char* animals_deserts[29] = { "camel", "scorpion", "spider", "snake", "jackal", "fox", "gazelle", "fennec", "kulan", "meerkat", "cobra", "varan", "lizard", "gerbil", "jeyran", "ostrich", "cheetah" , "coyote" , "cougar" , "goldeneagle" , "jay" , "eph" , "agama" , "gecko" , "meerkat" , "jackal" , "goat" , "hyena" , "caracal" };
    char* natural_areas[4] = { "tundra", "forests", "steppes", "deserts"};
    int money, area, animal;
    
    record* records = (record*)malloc(sizeof(record) * count);
    for (int i = 0; i < count; i++) {
        records[i].id = i;
        area = rand() % 4;
        strcpy(records[i].area, natural_areas[area]);
        switch (area) {
        case 0:
            strcpy(records[i].animal, animals_arctic[rand() % 25]);
            break;
        case 1:
            strcpy(records[i].animal, animals_forests[rand() % 30]);
            break;
        case 2:
            strcpy(records[i].animal, animals_steppes[rand() % 27]);
            break;
        case 3:
            strcpy(records[i].animal, animals_deserts[rand() % 29]);
            break;
        }
        money = rand() % 701 + 100;
        records[i].money = money;
    }
    fwrite(records, sizeof(record), count, file);
    fclose(file);
    free(records);
}

// Вывод записи
void printRecord(record rec) {
    printf("%5i: %15s | %25s | %4i", rec.id, rec.animal, rec.area, rec.money);
}

// Читаем записи из файла
record* readRecords(int* count, char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Unable open file\n");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    *count = ftell(file) / sizeof(record);
    rewind(file);
    record* records = malloc(*count * sizeof(record));
    fread(records, sizeof(record), *count, file);
    fclose(file);
    return records;
}

// Удаление записи
void deleteRecord(int id, char* filename, record** records, int* count) {
    record* rec = *records;
    int wrIndex = -1;
    for (int i = 0; i < *count; i++) {
        if (rec[i].id == id)
            wrIndex = i;
    }
    if (wrIndex < 0)
        return;
    *count -= 1;
    FILE* file = fopen(filename, "wb");
    fwrite(rec, sizeof(record), wrIndex, file);
    fwrite(rec + wrIndex + 1, sizeof(record), *count - wrIndex, file);
    fclose(file);
    *records = readRecords(count, filename);
}

// Добавление записи в файл
void addRecord(char* filename, record** records, int* count) {

    record newRecord;
    newRecord.id = (*records)[*count - 1].id + 1;
    *count = *count + 1;

    printf("Животное > ");
    scanf("%s", &newRecord.animal);
    printf("Ареал обитания > ");
    scanf("%s", &newRecord.area);
    printf("Затраты на содержание в день > ");
    scanf("%i", &newRecord.money);

    getchar();
    printRecord(newRecord);

    printf("\nЗаписать в файл? (y/n) > ");
    char answ = getchar();
    if (answ == 'y') {
        FILE* file = fopen(filename, "ab");
        fwrite(&newRecord, sizeof(record), 1, file);
        fclose(file);
        *records = readRecords(count, filename);
    }
    else {
        *count = *count - 1;
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    // Получаю имя файла
    char* filename = NULL;
    if (argc > 1) {
        filename = argv[1];
    }
    else {
        size_t nameSize;
        printf("Введите имя файла > ");
        filename = malloc(64 * sizeof(char));
        scanf("%s", filename);
        getchar();
    }

    // Получаю записи из файла
    int count = 100; // Количество записей в файле
    record* records = readRecords(&count, filename);
    if (records == NULL) {
        printf("Что то пошло не так, хотите создать новый файл? (y/n) > ");
        char answ = getchar();
        if (answ == 'y') {
            createRecords(60, filename);
            records = readRecords(&count, filename);
        }
        else
            return 0;
    }

    int recPerPage = 10; // Записей на страницу
    int page = 0, count_need_area, summ_money;
    char need_area[27], need_animal[27];

    while (1) {
        // Очищаю экран
        printf("\033[0d\033[2J\r");

        // Вывожу записи
        printf("Записи:\n");
        printf("    N        Название: |            Природная зона |  Затраты на корм\n");
        int start = page * recPerPage;
        int end = start + recPerPage;
        int pages = count / recPerPage + 1;
        for (int i = start; i < end; i++) {
            if (i >= count) {
                printf("\n");
                continue;
            }
            printRecord(records[i]);
            printf("\n");
        }

        // Меню
        printf("\n");
        printf("Cтраница: %i\n", page);
        printf("Навигация:\n");
        printf("n/p - след/пред\n");
        printf("a - добавить запись\n");
        printf("d - удалить запись\n");
        printf("e - вывести количество животных определенной зоны\n");
        printf("c - сколько денег тратися на определенное животное в месяц\n");
        printf("x - выйти\n");
        printf("> ");

        // Обрабатываю ввод
        char answ = getc(stdin);
        if (answ == 'n') {
            page = (page + 1) % pages;
        }
        else if (answ == 'p') {
            page = (page - 1) % pages;
            if (page < 0)
                page = pages - 1;
        }
        else if (answ == 'a') {
            addRecord(filename, &records, &count);
        }
        else if (answ == 'd') {
            int dIndex;
            printf("Номер записи для удаления > ");
            scanf("%i", &dIndex);
            deleteRecord(dIndex, filename, &records, &count);
        }
        else if (answ == 'e') {
            
            FILE* file = fopen(filename, "rb");

            // Очищаю экран
            printf("\033[0d\033[2J\r");

            // Запрашиваю зону
            printf("Введите нужную природную зону > ");
            scanf("%s", &need_area);
            count_need_area = 0;
            record rec;
            // Вывожу нужные записи
            printf("Записи:\n");
            printf("    N        Название: |            Природная зона |  Затраты на корм\n");
            for (int i = 0; i < count; i++) {
                fread(&rec, sizeof(record), 1, file);
                if (!strcmp(need_area, rec.area)) {
                    printRecord(records[i]);
                    printf("\n");
                    count_need_area += 1;
                }
            }
            printf("Всего записей: %d\n", count_need_area);

            fclose(file);

            printf("\nНажмите любую клавишу, чтобы вернуться в главное меню...");
            getch();
        }
        else if (answ == 'c') {

            // Очищаю экран
            printf("\033[0d\033[2J\r");

            // Запрашиваю животное
            printf("Введите нужное животное > ");
            scanf("%s", &need_animal);
            summ_money = 0;

            // Вывожу нужные записи
            printf("Записи:\n");
            printf("    N        Название: |            Природная зона |  Затраты на корм в месяц\n");
            for (int i = 0; i < count; i++) {
                if (!strcmp(need_animal, records[i].animal)) {
                    printf("%5i: %15s | %25s | %6i", records[i].id, records[i].animal, records[i].area, records[i].money * 30);
                    printf("\n");
                    summ_money += records[i].money * 30;
                }
            }
            printf("Общая сумма содержания данного вида животного за месяц: %d\n", summ_money);

            printf("\nНажмите любую клавишу, чтобы вернуться в главное меню...");
            getch();
        }
        else if (answ == 'x') {
            printf("\033[0d\033[2J\r");
            break;
        }
    }

    free(records);
    return 0;
}