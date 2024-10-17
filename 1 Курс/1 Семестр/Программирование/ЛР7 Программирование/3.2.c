/*
3. ���������� ��������� ����� � ������������ �����. ��������
���������� �����, �������� � ������ ������������� ���������� ������, �
�� ������������� ��������� ������� �������� ���������.
2) ��������� ��������� �����.

���������� ������� ���������.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>

int main(int argc, char* argv[]) {

	setlocale(0, "Rus");

	char filename[256];
	FILE* f;

	//�������� �����.
	if (argc != 2) {
		do {
			printf("������� ��� �����: ");
			scanf("%s", filename);
			f = fopen(filename, "rb+");
		} while (f == NULL);
	}
	else {
		strcpy(filename, argv[1]);
		f = fopen(filename, "rb+");
		if (f == NULL) {
			printf("�� ������� ������� ����.\n");
			do {
				printf("������� ��� �����: ");
				scanf("%s", filename);
				f = fopen(filename, "rb+");
			} while (f == NULL);
		}
	}

	int count = 0;
	float x = 0, first, last;

	printf("��������� ����\n");
	while (fread(&x, sizeof(float), 1, f)){
		printf("%.2f ", x);
		count++;
	}
	printf("\n\n");

	//������ �����.
	fseek(f, 0, SEEK_SET);
	float* nums = (float*)malloc(count * sizeof(float));

	//������ � ��������� ����������.
	for (int i = 0; i < count; i++) {
		fread(&x, sizeof(float), 1, f);
		nums[i] = x;
		if (i == 0) {
			first = nums[i];
		}
		if (i == count - 1) {
			last = nums[i];
		}
	}
	printf("������ ���������: %.2f\t��������� ���������: %.2f\n\n", first, last);

	//������ �����.
	fseek(f, 0, SEEK_SET);


	//���������.
	for (int i = 0; i < count; i++) {
		if (nums[i] > 0) {
			nums[i] += first;
		}
		else if (nums[i] < 0) {
			nums[i] -= last;
		}
		printf("%.2f ", nums[i]);
	}

	//����� ���������� � ����.
	for (int i = 0; i < count; i++) {
		fwrite(&nums[i], sizeof(float), 1, f);
	}
	
	fclose(f);

	printf("\n");
	system("pause");
	return 0;
}