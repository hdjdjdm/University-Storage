/*
Найти сумму элементов массива А(45), расположенных между макси -
мальным и минимальным элементами.Положение максимума и минимума в
массиве может быть любым, если они являются соседними элементами, выве -
сти сообщение об этом.Массивы, в которых максимальное или минимальное
значение встречается неоднократно, считать некорректными.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N 45

int main() {
	int A[N];
	srand(time(NULL));

	//Случайные элементы массива.
	for (int i = 0; i < N; i++) {
		A[i] = rand() % 201 - 100;
		printf("%d ", A[i]);
	}
	printf("\n");

	////Ввод элементов вручную
	//printf("Enter %i elements of massive: ", N);
	//for (int i = 0; i < N; i++) {
	//	scanf("%d", &A[i]);
	//}

	//Поиск максимального и миниального элементов массива.
	int max = A[0], min = A[0];
	int maxi = 0, mini = 0;
	for (int i = 0; i < N; i++) {
		if (max > A[i]) {
			max = A[i];
			maxi = i;
		}
	}
	for (int i = 0; i < N; i++) {
		if (min < A[i]) {
			min = A[i];
			mini = i;
		}
	}

	//Проверка массива по условию.
	int maxcount = 0, mincount = 0;
	for (int i = 0; i < N; i++) {
		if (A[i] == max)
			maxcount++;
		if (A[i] == min)
			mincount++;
	}
	if (maxcount > 1 || mincount > 1) {
		printf("Massive incorrect");
		system("pause");
		return 0;
	}

	//Сумма элементов между max и min элементами массива.
	int sum = 0;
	if (maxi + 1 == mini || mini + 1 == maxi) {
		printf("Max and Min nearby");
		system("pause");
		return 0;
	}
	if (mini < maxi) {
		for (int i = mini + 1; i < maxi; i++)
			sum += A[i];
	}
	else
		for (int i = maxi + 1; i < mini; i++)
			sum += A[i];
	printf("Summ = %d\n", sum);
	system("pause");
	return 0;
}
