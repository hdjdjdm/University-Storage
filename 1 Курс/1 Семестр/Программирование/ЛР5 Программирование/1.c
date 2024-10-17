/*
1. �������� ������� ���������� �� ������ �������� ������� � (7�8)
� ������� � (76). ���� � ������� ���������� �� ������ �������� �����������
������������, ����� ������ ���������� ������������.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>
#define I 7
#define J 8
#define K 76

//������ ���� ��������� ������� A.
void mA(int A[I][J]) {
	printf("\n������� �������� ������� A[%ix%i]: \n", I, J);
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			scanf("%i", &A[i][j]);
		}
	}
}

//������ ����  ������� B.
void mB(int B[K]) {
	printf("\n������� �������� ������� B[%i]: \n", K);
	for (int i = 0; i < K; i++) {
		scanf("%i", &B[i]);
	}
}

//��������������� ���� ��������� ������� A.
void amA(int A[I][J]) {
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			A[i][j] = rand() % 1001 - 500;
		}
	}
}

//��������������� ���� ������� B.
void amB(int B[K]) {
	for (int i = 0; i < K; i++) {
		B[i] = rand() % 1001 - 500;
	}
}

//����� ������� A.
void prA(int A[I][J]) {
	printf("������� A: \n");
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			printf("%i\t", A[i][j]);
		}
		printf("\n");
	}
}

//����� ������� B.
void prB(int B[K]) {
	printf("������ B: \n");
	for (int i = 0; i < K; i++)
		printf("%i ", B[i]);
	printf("\n");
}

int main() {

	setlocale(LC_ALL, "Russian");
	srand(time(NULL));


	int i, j;
	int A[I][J], B[K];

	//����� ������� ��� ��������������� ������ ����������.
	int choise;
	bool run;
	printf("��������:\n1. ���� �������\n2. �������������� ����\n");
	do {
		run = 1;
		scanf_s("%i", &choise);
		switch (choise) {
		case 1:
			//���� ��������� ������� A �������.
			mA(A);
			//���� ��������� ������� B �������.
			mB(B);
			break;
		case 2:
			//��������� �������� ������� A.
			amA(A);
			//��������� �������� ������� B.
			amB(B);
			break;
		default:
			printf("�������� 1 ��� 2: ");
			run = 0;
		}
	} while (run == 0);

	//����� ������� A � ������� B.
	printf("\n");
	prA(A);
	printf("\n");
	prB(B);

	printf("\n");

	//����� ������������� �� ������ �������� ������� A.
	int maxa = 0, maxai = 0, maxaj = 0;
	for (i = 0; i < I; i++) {
		for (j = 0; j < J; j++) {
			if (abs(A[i][j]) > abs(maxa)) {
				maxa = A[i][j];
				maxai = i;
				maxaj = j;
			}
		}
	}
	printf("������������ ������� ������� A �� ������ = %i\n", maxa);

	//����� ������������� �� ������ �������� ������� B.
	int maxb = 0, maxbi = 0, c = 0;
	for (i = 0; i < K; i++) {
		if (abs(B[i]) > abs(maxb)) {
			maxb = B[i];
			maxbi = i;
			c = 0;
		}
		if (abs(B[i]) == abs(maxb))
			c++;
	}

	//�������� ������� �� �������.
	if (c > 1) {
		printf("��������� �������! ��������� ����������� ������������ �� ������ ��������� � ������� B.\n");
		system("pause");
		return 0;
	}

	printf("������������ ������� ������� B �� ������ = %i\n", maxb);

	//����� ������� ������������� �� ������ ��������� ������� A � ������� B.
	A[maxai][maxaj] = maxb;
	B[maxbi] = maxa;

	//����� ����� ������� A � ������� B.
	printf("\n����� ");
	prA(A);
	printf("\n����� ");
	prB(B);
	system("pause");
	return 0;
}