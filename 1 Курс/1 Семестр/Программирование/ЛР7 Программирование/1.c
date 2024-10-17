/*
1. Дан файл, содержащий некоторый текст. Оставить в этом файле
только те фразы, в которых имеется числовая информация (то есть слова,
состоящие только из цифр, а для среднего и высокого уровней и сокращенная
запись числительных вида "1-й").

Повышенный уровень сложности.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


int main(int argc, char* argv[]) {

	setlocale(0, "Rus");

	char filename[256];
	FILE* f;

	//Открытие файла.
	if (argc != 2) {
		do {
			printf("Введите имя файла: ");
			scanf("%s", filename);
			f = fopen(filename, "r");
		} while (f == NULL);
	}
	else {
		strcpy(filename, argv[1]);
		f = fopen(filename, "r");
		if (f == NULL) {
			printf("Не удается открыть файл.\n");
			do {
				printf("Введите имя файла: ");
				scanf("%s", filename);
				f = fopen(filename, "r");
			} while (f == NULL);
		}
	}

	char buf[10000] = "", buf2[10000] = "", word[256] = "", sent[1024] = "";
	int i = 0, j = 0, k = 0, l = 0, r = 0;
	int fl1 = 0, fl2 = 0, us = 0;

	//Копирование файла в буфер.
	while (!feof(f)) {
		buf[i++] = getc(f);
	}
	fclose(f);
	buf[i] = '\0';

	//Текст файла.
	for (i = 0; buf[i + 1] != '\0'; i++) {
		printf("%c", buf[i]);
	}
	printf("\n\n");

	//Фильтрация файла.
	for (i = 0; buf[i] != '\0'; i++) {
		word[j++] = buf[i];
		sent[k++] = buf[i];

		if (buf[i] >= '0' && buf[i] <= '9') {
			fl1++;
		}
		if (i > 0 && buf[i - 1] == '-' && buf[i] == 'й') {
			us++;
		}
		if (buf[i] == ' ' || buf[i] == ',' || buf[i] == '.' || buf[i] == '\n' || buf[i + 1] == '\0') {
			if (fl1 > 0 && fl1 == j - 1 || us > 0) {
				fl2++;
			}
			fl1 = 0;
			us = 0;
			j = 0;
		}
		if (buf[i] == '.' || buf[i + 1] == '\0') {
			if (fl2 > 0) {
				for (l = 0; l < k; l++) {
					buf2[r++] = sent[l];
				}
			}
			fl1 = 0;
			us = 0;
			j = 0;
			fl2 = 0;
			k = 0;
		}
	}
	buf2[r++] = '\0';

	f = fopen(filename, "w");

	for (i = 0; buf2[i + 1] != '\0'; i++) {
		fputc(buf2[i], f);
		printf("%c", buf2[i]);
	}
	fclose(f);

	system("pause");
	return 0;
}