/*
Сформировать новый массив из положительных нечетных элементов
заданного линейного целочисленного массива.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define maxsize 100

int main() {
	int* A = NULL, * B = NULL;
	int size, i, bi = 0;
	srand(time(NULL));

	// Длина массива.
	do {
		printf("Enter len of massive from 0 to %d: ", maxsize);
		scanf("%d", &size);
		if (size < maxsize)
			break;
	} while (1);
	printf("\n");

	//Динамический массив A
	A = (int*)malloc(size * sizeof(int));

	////Случайные элементы массива.
	//for (int i = 0; i < size; i++) {
	//	A[i] = rand() % 201 - 100;
	//	printf("%i ", A[i]);
	//}
	//printf("\n\n");

	//Ввод элементов вручную
	printf("Enter %d elements of massive: \n", size);
	for (int i = 0; i < size; i++) {
		scanf("%d", &A[i]);
	}

	//Новый массив с заданными условиями
	B = (int*)malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		if (A[i] > 0 && A[i] % 2 != 0) {
			B[bi] = A[i];
			bi++;
		}
	}
	for (i = 0; i < bi; i++)
		printf("%d ", B[i]);
	printf("\n");
	free(A);
	free(B);
	system("pause");
	return 0;
}