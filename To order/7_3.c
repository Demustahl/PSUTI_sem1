#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <locale.h>

int main(void) {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int mass[15];
    int mass_2[15];
    int chislo = -1;
    int k;
    FILE* f;

    for (int i = 0; i < 15; i++) {
        mass[i] = rand() % 101;
    }

    f = fopen("bin.bin", "wb");
    if (f != NULL) {
        fwrite(mass, sizeof(int), 15, f);
    }
    fclose(f);

    printf("Изначальный массив:\n");
    f = fopen("bin.bin", "rb");
    if (f != NULL) {
        for (int i = 0; i < 15;i++) {
            fread(&mass_2, sizeof(int), 15, f);
            printf("%d ", mass_2[i]);
        }
    }
    fclose(f);

    f = fopen("bin.bin", "wb");
    fwrite(&chislo, sizeof(int), 1, f);
    k = mass_2[0];
    for (int i = 0, k = 0;i < 15;i++) {
        if (mass_2[i] > k) {
            k = mass_2[i];
        }
        fwrite(&mass_2[i], sizeof(int), 1, f);
        if (i == 14) {
            k++;
            fwrite(&k, sizeof(int), 1, f);
        }
    }
    fclose(f);

    f = fopen("bin.bin", "rb");
    printf("\nИтоговый массив:\n");
    for (int i = 0;i < 17;i++) {
        fread(&chislo, sizeof(int), 1, f);
        printf("%d ", chislo);
    }
    fclose(f);

    system("pause");
    return 0;
}