/*
2. Даны матрицы В(m, n) и С(n, m).Определить, есть ли в заданных матрицах строки,
содержащие по два положительных элемента. Вывести номера таких строк.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

//Ручной ввод матрицы.
void mt(int A[40][40], int I, int J) {
	printf("\nВведите элементы матрицы [%ix%i]: \n", I, J);
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			scanf("%i", &A[i][j]);
		}
	}
}

//Автоматичкеский ввод матрицы.
void am(int A[40][40], int I, int J) {
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			A[i][j] = rand() % 201 - 100;
		}
	}
}

//Вывод матрицы.
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

	//Выбор размера матрицы
	printf("Введите m и n:\n");
	scanf("%i %i", &m, &n);

	int B[40][40], C[40][40];

	//Выбор Ручного или Автоматического режима заполнения.
	int choise;
	bool run;
	printf("Выберите:\n1. Ввод вручную\n2. Автоматический ввод\n");
	do {
		run = 1;
		scanf("%i", &choise);
		switch (choise) {
		case 1:
			//Ввод элементов матрицы B вручную.
			mt(B, m, n);
			//Ввод элементов массива C вручную.
			mt(C, n, m);
			break;
		case 2:
			//Случайные элементы матрицы B.
			am(B, m, n);
			//Случайные элементы массива C.
			am(C, n, m);
			break;
		default:
			printf("Выберите 1 или 2: ");
			run = 0;
		}
	} while (run == 0);

	//Вывод матрицы B и С.
	printf("\nМатрица B: \n");
	pr(B, m, n);
	printf("\nМатрица C: \n");
	pr(C, n, m);

	printf("\n");

	//Строки с двумя положительными элементами
	int k = 0, kx = 0;

	printf("В матрице B 2 положительных элемента имеют строки: ");
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
		printf("Ни одна");
	kx = 0;
	printf("\n");

	printf("В матрице C 2 положительных элемента имеют строки: ");
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
		printf("Ни одна");
	}
	printf("\n");

	system("pause");
	return 0;
}
