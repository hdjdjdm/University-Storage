/*
Дана вещественная матрица D(7х9).Упорядочить(переставить)
строки матрицы по возрастанию сумм элементов строк.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define I 7
#define J 9


int main() {
	double D[I][J], A[I + 1][J + 1], S[I];
	int i, j, k;

	//Матрица D(IxJ) заполненная случайными элементами.
	printf("Matrix: \n");
	srand(time(NULL));
	for (i = 0; i < I; i++) {
		for (j = 0; j < J; j++) {
			D[i][j] = 0.01 * (rand() % 1001) - 5;
			printf("%.2lf\t", D[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	////Ввод элементов вручную
	//printf("Enter %d elements of matrix: \n", I * J);
	//for (i = 0; i < I; i++) {
	//	for (j = 0; j < J; j++) {
	//		scanf("lf", D[i][j]);
	//	}
	//}
	//printf("\nYour matrix: \n");
	//for (i = 0; i < I; i++) {
	//	for (j = 0; j < J; j++)
	//		printf("%lf\t", D[i][j]);
	//	printf("\n");
	//}
	//printf("\n");

	//Поиск сумм строк.
	for (i = 0; i < I; i++) {
		for (j = 0; j < J; j++)
			S[i] += D[i][j];
	}
	printf("Summ of rows: \n");
	for (i = 0; i < I; i++) {
		printf("%.2lf\n", S[i]);
	}
	printf("\n");

	//Добавляем сумму слева от матрицы.
	printf("Matrix with sums of rows: \n");
	for (i = 0; i < I; i++) {
		for (j = 0; j < (J + 1); j++) {
			if (j == 0)
				A[i][j] = S[i];
			else
				A[i][j] = D[i][j - 1];
		}
	}

	for (i = 0; i < I; i++) {
		for (j = 0; j < (J + 1); j++)
			printf("%.2lf\t", A[i][j]);
		printf("\n");
	}
	printf("\n");

	//Сортируем новую матрицу.
	double x;
	for (i = 0; i < I - 1; i++) {
		for (k = 0; k < I - 1; k++) {
			if (A[k][0] > A[k + 1][0]) {
				for (j = 0; j < J; j++) {
					x = A[k][j];
					A[k][j] = A[k + 1][j];
					A[k + 1][j] = x;
				}
			}
		}
	}

	printf("Sorted matrix with sums of rows: \n");
	for (i = 0; i < I; i++) {
		for (j = 0; j < (J + 1); j++)
			printf("%.2lf\t", A[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("Result: \n");
	for (i = 0; i < I; i++) {
		for (j = 0; j < J; j++)
			printf("%.2lf\t", A[i][j + 1]);
		printf("\n");
	}
	system("pause");
	return 0;
}