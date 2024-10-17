/*
Определить среднее арифметическое значение элементов квадратной
матрицы, лежащих на главной диагонали.
1) матрицу записать в виде статического двумерного массива;
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define maxsize 100

int main() {
	int x, i, j;
	float del = 0;
	int A[100][100];
	srand(time(NULL));

	//Размер матрицы.
	do {
		printf("Enter size of square matrix from 0 to %i: ", maxsize);
		scanf("%d", &x);
		if (x < maxsize)
			break;
	} while (1);

	//Случайные элементы матрицы
	for (i = 0; i < x; i++) {
		for (j = 0; j < x; j++) {
			A[i][j] = rand() % 101;
			printf("%d\t", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	////Ввод элементов вручную
	//printf("Enter %i elements of square matrix: \n", x*x);
	//for (i = 0; i < x; i++) {
	//	for (j = 0; j < x; j++) {
	//		scanf("%d", &A[i][j]);
	//	}
	//}

	//Сумма элементов главной диагонали.
	for (i = 0; i < x; i++) {
		for (j = 0; j < x; j++) {
			if (i == j) {
				del += A[i][j];
			}
		}
	}

	//Среднее арифметическое элементов главной диагонали.
	float Sr = del / x;
	printf("Average of main diagonal A[%dx%d] = %.2lf\n", x, x, Sr);
	system("pause");
	return 0;
}
