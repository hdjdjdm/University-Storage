/*
2. ���� ������� �(m, n) � �(n, m).����������, ���� �� � �������� �������� ������,
���������� �� ��� ������������� ��������. ������� ������ ����� �����.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

//������ ���� �������.
void mt(int A[40][40], int I, int J) {
	printf("\n������� �������� ������� [%ix%i]: \n", I, J);
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			scanf("%i", &A[i][j]);
		}
	}
}

//��������������� ���� �������.
void am(int A[40][40], int I, int J) {
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			A[i][j] = rand() % 201 - 100;
		}
	}
}

//����� �������.
void pr(int A[40][40], int I, int J) {
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			if (A[i][j] >= 0)
				printf(" ");
			printf("%i\t", A[i][j]);
		}
		printf("\n");
	}
}


int main() {

	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	int i, j, m, n;

	//����� ������� �������
	printf("������� m � n:\n");
	scanf("%i %i", &m, &n);

	int B[40][40], C[40][40];

	//����� ������� ��� ��������������� ������ ����������.
	int choise;
	bool run;
	printf("��������:\n1. ���� �������\n2. �������������� ����\n");
	do {
		run = 1;
		scanf("%i", &choise);
		switch (choise) {
		case 1:
			//���� ��������� ������� B �������.
			mt(B, m, n);
			//���� ��������� ������� C �������.
			mt(C, n, m);
			break;
		case 2:
			//��������� �������� ������� B.
			am(B, m, n);
			//��������� �������� ������� C.
			am(C, n, m);
			break;
		default:
			printf("�������� 1 ��� 2: ");
			run = 0;
		}
	} while (run == 0);

	//����� ������� B � �.
	printf("\n������� B: \n");
	pr(B, m, n);
	printf("\n������� C: \n");
	pr(C, n, m);

	printf("\n");

	//������ � ����� �������������� ����������
	int k = 0, kx = 0;

	printf("� ������� B 2 ������������� �������� ����� ������: ");
	for (i = 0; i < m; i++) {
		for (j = 0;j < n; j++) {
			if (B[i][j] > 0)
				k++;
		}
		if (k == 2) {
			printf("%i ", (i + 1));
			kx++;
		}
		k = 0;
	}
	if (kx == 0)
		printf("�� ����");
	kx = 0;
	printf("\n");

	printf("� ������� C 2 ������������� �������� ����� ������: ");
	for (i = 0; i < n; i++) {
		for (j = 0;j < m; j++) {
			if (C[i][j] > 0)
				k++;
		}
		if (k == 2) {
			printf("%i ", (i + 1));
			kx++;
		}
		k = 0;
	}
	if (kx == 0) {
		printf("�� ����");
	}
	printf("\n");

	system("pause");
	return 0;
}
