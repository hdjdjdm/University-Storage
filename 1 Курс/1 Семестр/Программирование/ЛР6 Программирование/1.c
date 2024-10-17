/*
1. Дана строка символов. Поменять местами первое и последнее слова.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

int main() {

	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int p1, p2, i, i2 = 0, i3 = 0;

	//Строка
	char s[1024], fw[32], lw[32], mid[256]="", s2[1024]="";
	printf("Введите предложение.\n");
	fgets(s, 1023, stdin);

	//Поиск первого и последнего пробелов
	for (i = 0; s[i] != '\0'; i++) {
		if (s[i] == ' ') {
			p1 = i;
			break;
		}
	}
	for (i = 0; s[i] != '\0'; i++) {
		if (s[i] == ' ') {
			p2 = i;
		}
	}

	//Середина
	for (i = p1; i <= p2; i++) {
		mid[i2++] = s[i];
	}
	mid[i2] = '\0';

	//Первое и последнее слово
	strncpy(fw, s, p1);
	fw[p1] = '\0';
	for (i = p2+1; s[i+1] != '\0'; i++) {
		lw[i3++] = s[i];
	}
	lw[i3] = '\0';

	//Замена первого и последнего слова
	strcat(s2, lw);
	strcat(s2, mid);
	strcat(s2, fw);

	printf("%s\n", s2);

	system("pause");
	return 0;
}
