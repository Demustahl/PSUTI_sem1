#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int index;
  int year;
  char county[16];
  char metal[16];
  int value;
  int count;
  int cost;
} record;

void createRecords(int count, char *filename) {
  FILE *file = fopen(filename, "wb");
  char *countrys[5] = {"Russia", "Brazil", "USA", "Belarus", "Armenia"};
  char *metals[5] = {"Bronze", "Gold", "Steel", "Nickel", "Tin"};
  record *records = (record *)malloc(sizeof(record) * count);
  for (int i = 0; i < count; i++) {
    records[i].index = i;
    records[i].year = 1500 + rand() % 400;
    strcpy(records[i].county, countrys[rand() % 5]);
    strcpy(records[i].metal, metals[rand() % 5]);
    records[i].value = rand() % 100 * 5;
    records[i].count = rand() % 1000;
    records[i].cost = rand() % 10000;
  }
  fwrite(records, sizeof(record), count, file);
  fclose(file);
  free(records);
}

void printRecord(record rec) {
  printf("%5i: %iг. %7s, %6s, номинал: %3i, %3i штук, %iр.", rec.index,
         rec.year, rec.county, rec.metal, rec.value, rec.count, rec.cost);
}

record *readRecords(int *count, char *filename) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    printf("Unable open file\n");
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  *count = ftell(file) / sizeof(record);
  rewind(file);
  record *records = malloc(*count * sizeof(record));
  fread(records, sizeof(record), *count, file);
  fclose(file);
  return records;
}

void sortRecords(record **distLink, record **srcLink, int *count, int *dstCount,
                 int century) {
  record *dist = *distLink;
  record *src = *srcLink;
  *dstCount = 0;
  for (int i = 0; i < *count; i++) {
    if ((src[i].year / 100 + 1) < century) {
      dist[*dstCount] = src[i];
      *dstCount += 1;
    }
  }

  record *tmpRecord = *srcLink;
  *srcLink = *distLink;
  *distLink = tmpRecord;

  int tmpCount = *dstCount;
  *dstCount = *count;
  *count = tmpCount;
}

void undoSort(record **dist, record **src, int *count, int *dstCount) {
  record *tmpRecord = *src;
  *src = *dist;
  *dist = tmpRecord;

  int tmpCount = *dstCount;
  *dstCount = *count;
  *count = tmpCount;
}

int getCostSum(record *recs, int count) {
  int sum = 0;
  for (int i = 0; i < count; i++) {
    sum += recs[i].cost;
  }
  return sum;
}

void deleteRecord(int index, char *filename, record **records, int *count) {
  record *rec = *records;
  int wrIndex = -1;
  for (int i = 0; i < *count; i++) {
    if (rec[i].index == index)
      wrIndex = i;
  }
  if (wrIndex < 0)
    return;
  *count -= 1;
  FILE *file = fopen(filename, "wb");
  fwrite(rec, sizeof(record), wrIndex, file);
  fwrite(rec + wrIndex + 1, sizeof(record), *count - wrIndex, file);
  fclose(file);
  *records = readRecords(count, filename);
}

void addRecord(char *filename, record **records, int *count) {

  record newRecord;
  newRecord.index = (*records)[*count - 1].index + 1;
  *count = *count + 1;
  printf("Введите год > ");
  scanf("%i", &newRecord.year);
  printf("Введите страну > ");
  scanf("%s", newRecord.county);
  printf("Введите металл > ");
  scanf("%s", newRecord.metal);
  printf("Введите номинал > ");
  scanf("%i", &newRecord.value);
  printf("Введите количество > ");
  scanf("%i", &newRecord.count);
  printf("Введите рыночную стоимость > ");
  scanf("%i", &newRecord.cost);
  getchar();
  printRecord(newRecord);

  printf("\nЗаписать в файл? (y/n) > ");
  char answ = getchar();
  if (answ == 'y') {
    FILE *file = fopen(filename, "ab");
    fwrite(&newRecord, sizeof(record), 1, file);
    fclose(file);
    *records = readRecords(count, filename);
  }
}

int main(int argc, char *argv[]) {
  //Получаю имя файла
  char *filename = NULL;
  if (argc > 1) {
    filename = argv[1];
  } else {
    size_t nameSize;
    printf("Введите имя файла > ");
    filename = malloc(64 * sizeof(char));
    scanf("%s", filename);
    getchar();
  }

  //Получаю записи из файла
  int count = 100; //Колличество записей в файле
  record *records = readRecords(&count, filename);
  if (records == NULL) {
    printf("Что то пошло не так, хотите создать новый файл? (y/n) > ");
    char answ = getchar();
    if (answ == 'y') {
      createRecords(35, filename);
      records = readRecords(&count, filename);
    } else
      return 0;
  }

  int tmpCount = 0; //Колличество отсортированных записей
  record *tmpRecords = malloc(count * sizeof(record)); //Отсортированные записи

  int recPerPage = 10; //Записей на страницу
  int page = 0;

  int sortMode = 0;

  int costSum = getCostSum(records, count);

  while (1) {
    // Очищаю экран
    printf("\033[0d\033[2J\r");

    //Вывожу записи
    printf("Записи:\n");
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

    //Меню
    printf("Сумарная стоимость коллекции: %iр.\n", costSum);
    printf("Cтраница: %i\n", page);
    printf("Навигация:\n");
    printf("n/p - след/пред\n");
    if (!sortMode) {
      printf("a - добавить запись\n");
      printf("d - удалить запись\n");
      printf(
          "f - вывести сведения о монетах, выпущенных ранее указанного века\n");
    }
    printf("c - переключить фильтр\n");
    printf("x - выйти\n");
    printf("> ");

    //Обрабатываю ввод
    char answ = getc(stdin);
    if (answ == 'n') {
      page = (page + 1) % pages;
    } else if (answ == 'p') {
      page = (page - 1) % pages;
      if (page < 0)
        page = pages - 1;
    } else if (answ == 'a' && !sortMode) {
      addRecord(filename, &records, &count);
    } else if (answ == 'd' && !sortMode) {
      int dIndex;
      printf("Номер записи для удаления > ");
      scanf("%i", &dIndex);
      deleteRecord(dIndex, filename, &records, &count);
    } else if (answ == 'f' && !sortMode) {
      sortMode = 1;
      printf("Введите век > ");
      int century = 0;
      scanf("%i", &century);
      sortRecords(&tmpRecords, &records, &count, &tmpCount, century);
      costSum = getCostSum(records, count);
    } else if (answ == 'c') {
      undoSort(&records, &tmpRecords, &count, &tmpCount);
      costSum = getCostSum(records, count);
      sortMode = !sortMode;
    } else if (answ == 'x') {
      printf("\033[0d\033[2J\r");
      break;
    }
  }

  free(records);
  free(tmpRecords);
  return 0;
}