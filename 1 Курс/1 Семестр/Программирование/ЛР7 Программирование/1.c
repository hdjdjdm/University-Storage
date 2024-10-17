/*
1. ��� ����, ���������� ��������� �����. �������� � ���� �����
������ �� �����, � ������� ������� �������� ���������� (�� ���� �����,
��������� ������ �� ����, � ��� �������� � �������� ������� � �����������
������ ������������ ���� "1-�").

���������� ������� ���������.
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

	//�������� �����.
	if (argc != 2) {
		do {
			printf("������� ��� �����: ");
			scanf("%s", filename);
			f = fopen(filename, "r");
		} while (f == NULL);
	}
	else {
		strcpy(filename, argv[1]);
		f = fopen(filename, "r");
		if (f == NULL) {
			printf("�� ������� ������� ����.\n");
			do {
				printf("������� ��� �����: ");
				scanf("%s", filename);
				f = fopen(filename, "r");
			} while (f == NULL);
		}
	}

	char buf[10000] = "", buf2[10000] = "", word[256] = "", sent[1024] = "";
	int i = 0, j = 0, k = 0, l = 0, r = 0;
	int fl1 = 0, fl2 = 0, us = 0;

	//����������� ����� � �����.
	while (!feof(f)) {
		buf[i++] = getc(f);
	}
	fclose(f);
	buf[i] = '\0';

	//����� �����.
	for (i = 0; buf[i + 1] != '\0'; i++) {
		printf("%c", buf[i]);
	}
	printf("\n\n");

	//���������� �����.
	for (i = 0; buf[i] != '\0'; i++) {
		word[j++] = buf[i];
		sent[k++] = buf[i];

		if (buf[i] >= '0' && buf[i] <= '9') {
			fl1++;
		}
		if (i > 0 && buf[i - 1] == '-' && buf[i] == '�') {
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