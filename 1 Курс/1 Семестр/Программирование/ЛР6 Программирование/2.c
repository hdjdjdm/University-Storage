/*
2. Дана символьная строка. Проверить, все ли слова после точки
начинаются с заглавной буквы. Если нет – исправить.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <windows.h>

//Строчная ли буква.
bool low(char c) {
	char l[256] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяabcdefghijklmnopqrstuvwxyz";
	for (int i = 0; l[i] != '\0'; i++) {
		if (c == l[i]) {
			return 1;
		}
	}
	return 0;
}

char toup(char c) {
	char l[256] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяabcdefghijklmnopqrstuvwxyz";
	char u[256] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; l[i] != '\0'; i++) {
		if (c == l[i]) {
			c = u[i];
		}
	}
	return c;
}

int main() {

	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int c = 0;
	char s[256];
	printf("Введите строку:\n");
	fgets(s, 255, stdin);

	//Проверка.
	for (int i = 0; s[i + 2] != '\0'; i++) {
		if (s[i] == '.' && low(s[i + 2])) {
			s[i + 2] = toup(s[i + 2]);
			c++;
		}
	}

	//Результат.
	if (c > 0) {
		printf("\nНесколько (%d) слов после точки начинаются с маленькой буквы! Исправляю:\n", c);
		for (int i = 0; s[i] != '\0'; i++) {
			printf("%c", s[i]);
		}
		printf("\n");
		system("pause");
		return 0;
	}
	else {
		printf("\nВсе слова после точки начинаются с большой буквы!\n");
	}

	system("pause");
	return 0;
}
