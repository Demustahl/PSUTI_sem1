#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

char* trainType[3] = { "fast\0", "express\0", "passenger\0" };

typedef struct {
    int id;
    char dest[16];
    int number;
    int type;
    int depTime;
    int travelTime;
} record;

void createRecords(int count, char* filename) {
    FILE* file = fopen(filename, "wb");
    char* dest[5] = { "Saratov", "Penza", "Tolytti", "Moscow", "Syzran" };
    int trainNumber = 0;
    int depTime = 25200; // 7 утра
    // время между рейсами
    // 10 вечера минус 7 утра / кол-во рейсов
    int depTimeDelta = (72000 - depTime) / count;
    record* records = (record*)malloc(sizeof(record) * count);
    for (int i = 0; i < count; i++) {
        records[i].id = i;
        strcpy(records[i].dest, dest[rand() % 5]);
        trainNumber += rand() % 101 + 10;
        records[i].number = trainNumber;
        records[i].type = rand() % 3;
        depTime += depTimeDelta;
        records[i].depTime = depTime;
        records[i].travelTime = rand() % 15600 + 2400; // от 40 минут до 5 часов
    }
    fwrite(records, sizeof(record), count, file);
    fclose(file);
    free(records);
}

void printRecord(record rec) {
    int depHour = rec.depTime / 3600;
    int depMin = (rec.depTime % 3600) / 60;
    int travelHour = rec.travelTime / 3600;
    int travelMin = (rec.travelTime % 3600) / 60;
    printf("%5i: %10s | N %4i | %12s | %2i:%02i | %2i:%02i", rec.id, rec.dest,
        rec.number, trainType[rec.type], depHour, depMin, travelHour,
        travelMin);
}

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

void sortRecords(record** distLink, record** srcLink, int* count, int* dstCount,
    int fromTime, int toTime) {
    record* dist = *distLink;
    record* src = *srcLink;
    *dstCount = 0;
    for (int i = 0; i < *count; i++) {
        if (src[i].depTime > fromTime && src[i].depTime < toTime &&
            strcmp("Moscow", src[i].dest) == 0) {
            dist[*dstCount] = src[i];
            *dstCount += 1;
        }
    }

    record* tmpRecord = *srcLink;
    *srcLink = *distLink;
    *distLink = tmpRecord;

    int tmpCount = *dstCount;
    *dstCount = *count;
    *count = tmpCount;
}

void undoSort(record** dist, record** src, int* count, int* dstCount) {
    record* tmpRecord = *src;
    *src = *dist;
    *dist = tmpRecord;

    int tmpCount = *dstCount;
    *dstCount = *count;
    *count = tmpCount;
}

record findFastestTrain(record* recs, int count, int type) {
    int min = -1;
    record tar;
    tar.id = 0;
    tar.depTime = 0;
    tar.travelTime = 0;
    tar.number = 0;
    strcpy(tar.dest, "");
    tar.type = 2;
    for (int i = 0; i < count; i++) {
        if ((recs[i].travelTime < min || min == -1) &&
            (strcmp("Moscow", recs[i].dest) == 0 && recs[i].type == type)) {
            min = recs[i].travelTime;
            tar = recs[i];
        }
    }
    return tar;
}

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

void addRecord(char* filename, record** records, int* count) {

    record newRecord;
    newRecord.id = (*records)[*count - 1].id + 1;
    *count = *count + 1;

    printf("Город назначения > ");
    scanf("%s", newRecord.dest);
    printf("Номер поезда > ");
    scanf("%i", &newRecord.number);

    printf("0 - скорый\n1 - экспресс\n2 - пассажирский\nТип поезда > ");
    scanf("%i", &newRecord.type);

    int hours = 0;
    int minutes = 0;
    printf("Формат 'чч мм'(часы и минуты через пробел)\nОтправление с >");
    scanf("%i %i", &hours, &minutes);
    newRecord.depTime = hours * 3600 + minutes * 60;
    printf("Формат 'чч мм'(часы и минуты через пробел)\nВремя в пути >");
    scanf("%i %i", &hours, &minutes);
    newRecord.travelTime = hours * 3600 + minutes * 60;
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
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
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
            createRecords(35, filename);
            records = readRecords(&count, filename);
        }
        else
            return 0;
    }

    int tmpCount = 0; // Количество отсортированных записей
    record* tmpRecords = malloc(count * sizeof(record)); // Отсортированные записи

    int recPerPage = 10; // Записей на страницу
    int page = 0;

    int sortMode = 0;

    record fastestMoscowTrain = findFastestTrain(records, count, 0);

    while (1) {
        // Очищаю экран
        printf("\033[0d\033[2J\r");

        // Вывожу записи
        printf("Записи:\n");
        printf("    N       Назн: |  Номер |          Тип |  Отпр | В пути\n");
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
        printf("Быстрейший поезд до Москвы типа '%s':\n",
            trainType[fastestMoscowTrain.type]);
        printRecord(fastestMoscowTrain);
        printf("\n");
        printf("Cтраница: %i\n", page);
        printf("Навигация:\n");
        printf("n/p - след/пред\n");
        printf("e - Быстрейший поезд до Москвы типа : \n");
        if (!sortMode) {
            printf("a - добавить запись\n");
            printf("d - удалить запись\n");
            printf("f - вывести поезда в Москву за промежуток времени\n");
        }
        printf("c - переключить фильтр\n");
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
        else if (answ == 'a' && !sortMode) {
            addRecord(filename, &records, &count);
        }
        else if (answ == 'd' && !sortMode) {
            int dIndex;
            printf("Номер записи для удаления > ");
            scanf("%i", &dIndex);
            deleteRecord(dIndex, filename, &records, &count);
        }
        else if (answ == 'f' && !sortMode) {
            sortMode = 1;
            int hours = 0;
            int minutes = 0;
            int fromTime = 0;
            int toTime = 0;
            printf("Формат 'чч мм'(часы и минуты через пробел)\nОтправление с >");
            scanf("%i %i", &hours, &minutes);
            fromTime = hours * 3600 + minutes * 60;
            printf("Формат 'чч мм'(часы и минуты через пробел)\nОтправление по >");
            scanf("%i %i", &hours, &minutes);
            toTime = hours * 3600 + minutes * 60;
            sortRecords(&tmpRecords, &records, &count, &tmpCount, fromTime, toTime);
        }
        else if (answ == 'e') {
            printf(
                "0 - скорый\n1 - экспресс\n2 - пассажирский\nВведите тип поезда >");
            int type = 0;
            scanf("%i", &type);
            fastestMoscowTrain = findFastestTrain(records, count, type);
        }
        else if (answ == 'c') {
            undoSort(&records, &tmpRecords, &count, &tmpCount);
            sortMode = !sortMode;
        }
        else if (answ == 'x') {
            printf("\033[0d\033[2J\r");
            break;
        }
    }

    free(records);
    free(tmpRecords);
    return 0;
}