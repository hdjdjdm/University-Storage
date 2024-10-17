/*
2. ���� ���������� ������. ���������, ��� �� ����� ����� �����
���������� � ��������� �����. ���� ��� � ���������.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <windows.h>

//�������� �� �����.
bool low(char c) {
	char l[256] = "��������������������������������abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; l[i] != '\0'; i++) {
		if (c == l[i]) {
			return 1;
		}
	}
	return 0;
}

char toup(char c) {
	char l[256] = "��������������������������������abcdefghijklmnopqrstuvwxyz";
	char u[256] = "�����Ũ��������������������������ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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
	printf("������� ������:\n");
	fgets(s, 255, stdin);

	//��������.
	for (int i = 0; s[i + 2] != '\0'; i++) {
		if (s[i] == '.' && low(s[i + 2])) {
			s[i + 2] = toup(s[i + 2]);
			c++;
		}
	}

	//���������.
	if (c > 0) {
		printf("\n��������� (%d) ���� ����� ����� ���������� � ��������� �����! ���������:\n", c);
		for (int i = 0; s[i] != '\0'; i++) {
			printf("%c", s[i]);
		}
		printf("\n");
		system("pause");
		return 0;
	}
	else {
		printf("\n��� ����� ����� ����� ���������� � ������� �����!\n");
	}

	system("pause");
	return 0;
}
