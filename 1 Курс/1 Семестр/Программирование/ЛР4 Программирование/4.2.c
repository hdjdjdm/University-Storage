/*
Определить среднее арифметическое значение элементов квадратной
матрицы, лежащих на главной диагонали.
2) организовать динамическую матрицу, используя динамическое
выделение памяти.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define maxsize 100

int main() {
	int size, i, j;
	float del = 0;
	int** A = NULL;
	srand(time(NULL));

	//Размер матрицы.
	do {
		printf("Enter size of square matrix from 0 to %i: ", maxsize);
		scanf("%d", &size);
		if (size < maxsize)
			break;
	} while (1);

	//Динамическая матрица.
	A = (int**)malloc(size * sizeof(int*));
	for (i = 0; i < size; i++)
		A[i] = (int*)malloc(size * sizeof(int));

	//Случайные элементы матрицы.
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			A[i][j] = rand() % 101;
			printf("%i\t", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	////Ввод элементов вручную
	//printf("Enter %i elements of square matrix: \n", size * size);
	//for (i = 0; i < size; i++) {
	//	for (j = 0; j < size; j++) {
	//		scanf("%d", &A[i][j]);
	//	}
	//}

	//Сумма элементов главной диагонали.
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (i == j) {
				del += A[i][j];
			}
		}
	}

	//Среднее арифметическое элементов главной диагонали.
	float Sr = del / size;
	printf("Average of main diagonal A[%dx%d] = %.2lf\n", size, size, Sr);
	free(A);
	system("pause");
	return 0;
}
