/*
3. Компоненты бинарного файла – вещественные числа. Изменить
содержимое файла, прибавив к каждой положительной компоненте первую, а
из отрицательных компонент вычесть значение последней.
2) Обработка бинарного файла.

Повышенный уровень сложности.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>

int main(int argc, char* argv[]) {

	setlocale(0, "Rus");

	char filename[256];
	FILE* f;

	//Открытие файла.
	if (argc != 2) {
		do {
			printf("Введите имя файла: ");
			scanf("%s", filename);
			f = fopen(filename, "rb+");
		} while (f == NULL);
	}
	else {
		strcpy(filename, argv[1]);
		f = fopen(filename, "rb+");
		if (f == NULL) {
			printf("Не удается открыть файл.\n");
			do {
				printf("Введите имя файла: ");
				scanf("%s", filename);
				f = fopen(filename, "rb+");
			} while (f == NULL);
		}
	}

	int count = 0;
	float x = 0, first, last;

	printf("Начальный файл\n");
	while (fread(&x, sizeof(float), 1, f)){
		printf("%.2f ", x);
		count++;
	}
	printf("\n\n");

	//Начало файла.
	fseek(f, 0, SEEK_SET);
	float* nums = (float*)malloc(count * sizeof(float));

	//Первый и последний компоненты.
	for (int i = 0; i < count; i++) {
		fread(&x, sizeof(float), 1, f);
		nums[i] = x;
		if (i == 0) {
			first = nums[i];
		}
		if (i == count - 1) {
			last = nums[i];
		}
	}
	printf("Первый компонент: %.2f\tПоследней компонент: %.2f\n\n", first, last);

	//Начало файла.
	fseek(f, 0, SEEK_SET);


	//Результат.
	for (int i = 0; i < count; i++) {
		if (nums[i] > 0) {
			nums[i] += first;
		}
		else if (nums[i] < 0) {
			nums[i] -= last;
		}
		printf("%.2f ", nums[i]);
	}

	//Вывод результата в файл.
	for (int i = 0; i < count; i++) {
		fwrite(&nums[i], sizeof(float), 1, f);
	}
	
	fclose(f);

	printf("\n");
	system("pause");
	return 0;
}