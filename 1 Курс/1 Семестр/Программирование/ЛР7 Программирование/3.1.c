/*
3. ���������� ��������� ����� � ������������ �����. ��������
���������� �����, �������� � ������ ������������� ���������� ������, �
�� ������������� ��������� ������� �������� ���������.
1) �������� ��������� �����.

���������� ������� ���������.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>


int main(int argc, char* argv[]) {

	setlocale(0, "Rus");
	srand(time(NULL));

	char filename[256];
	FILE* f;

	//�������� �����.
	if (argc != 2) {
		do {
			printf("������� ��� �����: ");
			scanf("%s", filename);
			f = fopen(filename, "wb");
		} while (f == NULL);
	}
	else {
		strcpy(filename, argv[1]);
		f = fopen(filename, "wb");
		if (f == NULL) {
			printf("�� ������� ������� ����.\n");
			do {
				printf("������� ��� �����: ");
				scanf("%s", filename);
				f = fopen(filename, "wb");
			} while (f == NULL);
		}
	}

	int count;
	float x;

	printf("������� ���������� ������������ �����: ");
	scanf_s("%d", &count);
	for (int i = 0; i < count; i++) {
		x = 0.01 * (rand() % 1001) - 5;
		printf("%.2f ", x);
		fwrite(&x, sizeof(float), 1, f);
	}

	fclose(f);

	printf("\n");
	system("pause");
	return 0;
}