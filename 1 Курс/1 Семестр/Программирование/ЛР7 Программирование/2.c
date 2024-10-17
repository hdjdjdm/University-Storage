/*
2. � ��������� ����� �������� ������������� �������. �������������
�� � ������������ � �������� � ������ ���� � ��������� �� ������� �����
����� �����.

���������� ������� ���������.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>


int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "Rus");

	char filename[256], filename2[256];
	FILE* f, * f2;

	//�������� �����.
	if (argc != 3) {
		do {
			printf("������� ��� ����� ������: ");
			scanf("%s", filename);
			f = fopen(filename, "r");
		} while (f == NULL);
		do {
			printf("������� ��� ����� ������: ");
			scanf("%s", filename2);
			f2 = fopen(filename2, "w");
		} while (f2 == NULL);

	}
	else {
		strcpy(filename, argv[1]);
		strcpy(filename2, argv[2]);
		f = fopen(filename, "r");
		f2 = fopen(filename2, "w");
		if (f == NULL) {
			printf("�� ������� ������� ���� ������.\n");
			do {
				printf("������� ��� �����: ");
				scanf("%s", filename);
				f = fopen(filename, "r");
			} while (f == NULL);
		}
		if (f2 == NULL) {
			printf("�� ������� ������� ���� ������.\n");
			do {
				printf("������� ��� �����: ");
				scanf("%s", filename2);
				f2 = fopen(filename2, "w");
			} while (f2 == NULL);
		}
	}

	bool st = 0;
	int x = 0, mi = 1, mj = 1;
	char buf[512] = "";

	//����������� ����� � �����.
	while (!feof(f)) {
		buf[x++] = fgetc(f);
	}
	buf[x] = '\0';

	for (x = 0; buf[x + 1] != '\0'; x++) {
		printf("%c", buf[x]);
	}
	printf("\n\n");

	//����� ������� �������.
	for (x = 1; buf[x] != '\0'; x++) {
		if (st == 0 && buf[x] >= '0' && buf[x] <= '9' && (buf[x - 1] == ' ' || buf[x - 1] == '\t')) {
			mi++;
		}
		if (buf[x] == '\n') {
			mj++;
			st = 1;
		}
	}
	
	//������ �����
	fseek(f, 0, SEEK_SET);

	int matr[50][50];
	double matr2[50][50];

	for (int i = 0; i < mi; i++) {
		for (int j = 0; j < mj; j++) {
			fscanf(f, "%d", &matr[i][j]);
		}
	}

	for (int i = 0; i < mi; i++) {
		for (int j = 0; j < mj; j++) {
			matr2[i][j] = (double)matr[i][j];
		}
	}

	for (int i = 0; i < mi; i++) {
		for (int j = 0; j < mj; j++) {
			fprintf(f2, "%.2f\t", matr2[i][j]);
		}
		fprintf(f2, "\n");
	}

	fclose(f);
	fclose(f2);

	system("pause");
	return 0;
}