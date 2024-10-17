/*
1. Поменять местами наибольшие по модулю элементы матрицы А (7х8)
и массива В (76). Если в массиве наибольшее по модулю значение встречается
неоднократно, такой массив признается некорректным.
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

//Ручной ввод двумерной матрицы A.
void mA(int A[I][J]) {
	printf("\nВведите элементы матрицы A[%ix%i]: \n", I, J);
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			scanf("%i", &A[i][j]);
		}
	}
}

//Ручной ввод  массива B.
void mB(int B[K]) {
	printf("\nВведите элементы массива B[%i]: \n", K);
	for (int i = 0; i < K; i++) {
		scanf("%i", &B[i]);
	}
}

//Автоматичкеский ввод двумерной матрицы A.
void amA(int A[I][J]) {
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			A[i][j] = rand() % 1001 - 500;
		}
	}
}

//Автоматичкеский ввод массива B.
void amB(int B[K]) {
	for (int i = 0; i < K; i++) {
		B[i] = rand() % 1001 - 500;
	}
}

//Вывод матрицы A.
void prA(int A[I][J]) {
	printf("Матрица A: \n");
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			printf("%i\t", A[i][j]);
		}
		printf("\n");
	}
}

//Вывод массива B.
void prB(int B[K]) {
	printf("Массив B: \n");
	for (int i = 0; i < K; i++)
		printf("%i ", B[i]);
	printf("\n");
}

int main() {

	setlocale(LC_ALL, "Russian");
	srand(time(NULL));


	int i, j;
	int A[I][J], B[K];

	//Выбор Ручного или Автоматического режима заполнения.
	int choise;
	bool run;
	printf("Выберите:\n1. Ввод вручную\n2. Автоматический ввод\n");
	do {
		run = 1;
		scanf_s("%i", &choise);
		switch (choise) {
		case 1:
			//Ввод элементов матрицы A вручную.
			mA(A);
			//Ввод элементов массива B вручную.
			mB(B);
			break;
		case 2:
			//Случайные элементы матрицы A.
			amA(A);
			//Случайные элементы массива B.
			amB(B);
			break;
		default:
			printf("Выберите 1 или 2: ");
			run = 0;
		}
	} while (run == 0);

	//Вывод матрицы A и массива B.
	printf("\n");
	prA(A);
	printf("\n");
	prB(B);

	printf("\n");

	//Поиск максимального по модулю элемента матрицы A.
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
	printf("Максимальный элемент матрицы A по модулю = %i\n", maxa);

	//Поиск максимального по модулю элемента массива B.
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

	//Проверка массива по условию.
	if (c > 1) {
		printf("Нарушение условия! Несколько одиннаковых максимальных по модулю элементов в массиве B.\n");
		system("pause");
		return 0;
	}

	printf("Максимальный элемент массива B по модулю = %i\n", maxb);

	//Смена местами максимальноых по модулю элементов матрицы A и массива B.
	A[maxai][maxaj] = maxb;
	B[maxbi] = maxa;

	//Вывод новой матрицы A и массива B.
	printf("\nНовая ");
	prA(A);
	printf("\nНовый ");
	prB(B);
	system("pause");
	return 0;
}