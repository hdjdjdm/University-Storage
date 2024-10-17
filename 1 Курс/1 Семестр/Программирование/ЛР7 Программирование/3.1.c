/*
3. Компоненты бинарного файла – вещественные числа. Изменить
содержимое файла, прибавив к каждой положительной компоненте первую, а
из отрицательных компонент вычесть значение последней.
1) Создание бинарного файла.

Повышенный уровень сложности.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>


int main(int argc, char* argv[]) {

	setlocale(0, "Rus");
	srand(time(NULL));

	char filename[256];
	FILE* f;

	//Открытие файла.
	if (argc != 2) {
		do {
			printf("Введите имя файла: ");
			scanf("%s", filename);
			f = fopen(filename, "wb");
		} while (f == NULL);
	}
	else {
		strcpy(filename, argv[1]);
		f = fopen(filename, "wb");
		if (f == NULL) {
			printf("Не удается открыть файл.\n");
			do {
				printf("Введите имя файла: ");
				scanf("%s", filename);
				f = fopen(filename, "wb");
			} while (f == NULL);
		}
	}

	int count;
	float x;

	printf("Введите количество вещественных чисел: ");
	scanf_s("%d", &count);
	for (int i = 0; i < count; i++) {
		x = 0.01 * (rand() % 1001) - 5;
		printf("%.2f ", x);
		fwrite(&x, sizeof(float), 1, f);
	}

	fclose(f);

	printf("\n");
	system("pause");
	return 0;
}