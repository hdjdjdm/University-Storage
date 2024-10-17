/*
4. ���������� ����� ���������� ��������������� ������ �������� �
�����, ���������� ��������� ������: ������� �������� � ������ ��
������, ���������� � �����������. ������� ���������� ����� �� ������� ��
��������� � ������� ������ ���������, ������� ������ ���� �� �� ������
��������.

���������� �������.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <locale.h>
#include <stdbool.h>
#include <windows.h>

//����� �����.
void line() {
	for (int size = 0; size < 94; size++) {
		printf("-");
	}
	printf("\n");
}


int main(int argc, char* argv[]) {

	setlocale(0, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char filename[256];
	FILE* f;

	bool go;
	int choice = 0, yn;
	int phi[1000], mat[1000], inf[1000], phi2[1000], mat2[1000], inf2[1000];
	int num = 1, k = 0, i = 0, max = 0, l = 0, cd = 0;
	char name[1000][30], name2[1000][30];

	printf("����� ���������� � ���� ������ �����!\n\n");
	printf("�������� ���� �� ���������: \n1.������� ����� ����.\n2.������� ������������ ���� � ������������ ��������������.\n");
	do {
		scanf("%d", &choice);
		switch (choice) {
		case 1: {
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

			//���� ������ � ���������.
			do {
				printf("������� ������� ��������: ");
				scanf("%s", name[k]);
				printf("������� ��� ������ �� ������, ���������� � �����������: \n");
				scanf("%d %d %d", &phi[k], &mat[k], &inf[k]);

				do {
					go = 1;
					printf("�������� ��� ��������?\n1.��\n2.���\n");
					scanf("%d", &yn);
					switch (yn) {
					case 1:
						yn = 0;
						k++;
						max++;
						break;
					case 2:
						yn = 1;
						break;
					default:
						go = 0;
					}
				} while (go == 0);
			} while (yn == 0);


			//���� ������ � ����.
			for (k = 0; k <= max; k++) {
				fwrite(&name[k], sizeof(name[k]), 1, f);
				fwrite(&phi[k], sizeof(int), 1, f);
				fwrite(&mat[k], sizeof(int), 1, f);
				fwrite(&inf[k], sizeof(int), 1, f);
			}

			fclose(f);
			go = 1;
			break;
		}
		case 2: {
			//�������� �����.
			if (argc != 2) {
				do {
					printf("������� ��� �����: ");
					scanf("%s", filename);
					f = fopen(filename, "rb");
				} while (f == NULL);
			}
			else {
				strcpy(filename, argv[1]);
				f = fopen(filename, "rb");
				if (f == NULL) {
					printf("�� ������� ������� ����.\n");
					do {
						printf("������� ��� �����: ");
						scanf("%s", filename);
						f = fopen(filename, "rb");
					} while (f == NULL);
				}
			}

			while (true) {

				fread(&name[k], sizeof(name[k]), 1, f);
				fread(&phi[k], sizeof(int), 1, f);
				fread(&mat[k], sizeof(int), 1, f);
				fread(&inf[k], sizeof(int), 1, f);
				if (feof(f)) {
					max--;
					break;
				}
				k++;
				max++;
			}


			fclose(f);
			go = 1;
			break;
		}
		default:
			printf("�������� ������������ ����� ����.\n");
			go = 0;
		}
	} while (go == 0);



	int max2 = max, go2 = 0, del, k2 = 0, phic = 0, matc = 0, infc = 0, list = 1, lc = 0, maxlc;
	do {
		max = max2;
		maxlc = max2 / 5 + 1;
		//�������.
		system("cls");
		if (list > 1 && list < maxlc) {
			printf("%51s %d >>\n", " << ��������", list);
		}
		else if (list == 1) {
			printf("%51s %d >>\n", "��������", list);
		}
		else if (list == maxlc) {
			printf("%51s %d\n", " << ��������", list);
		}

		line();
		printf("|  �  |        ������� ��������        |    ������    |    ����������    |    �����������    |\n");
		line();

		for (k = lc; k < list * 5 && k <= max2; k++) {
			printf("|%5d|%32s|%14d|%18d|%19d|\n", num++, name[k], phi[k], mat[k], inf[k]);
			line();
		}

		printf("\n\n������ � ������:\n1.�������� ���������.\n2.������� ��������.\n3.�������� ������.\n\
4.������� ���������� ����� �� ������� �� ���������.\n5.������� ������ ���������, ������� ������ ���� �� �� ������ ��������.\n6.������>>\n7.�����<<\n8.������� ���������\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1: {
			//���������� � ���� ����� ������.
			f = fopen(filename, "ab");

			k = max2;
			do {
				k++;
				max2++;
				printf("������� ������� ��������: ");
				scanf("%s", name[k]);
				printf("������� ��� ������ �� ������, ���������� � �����������: \n");
				scanf("%d %d %d", &phi[k], &mat[k], &inf[k]);

				do {
					go = 1;
					printf("�������� ��� ��������?\n1.��\n2.���\n");
					scanf("%i", &yn);
					switch (yn) {
					case 1:
						yn = 0;
						break;
					case 2:
						yn = 1;
						break;
					default:
						go = 0;
					}
				} while (go == 0);
			} while (yn == 0);

			//���� ������ � ����.
			for (k = max + 1; k <= max2; k++) {
				fwrite(&name[k], sizeof(name[k]), 1, f);
				fwrite(&phi[k], sizeof(int), 1, f);
				fwrite(&mat[k], sizeof(int), 1, f);
				fwrite(&inf[k], sizeof(int), 1, f);
			}

			fclose(f);
			num = 1;
			lc = 0;
			list = 1;
			break;
		}
		case 2: {
			//�������� ���������.
			f = fopen(filename, "wb");

			do {
				k2 = 0;
				go = 1;
				printf("������� ����� ��������: ");
				scanf("%d", &del);
				del--;
				if (del <= max2 && del >= 0) {
					for (k = 0; k < del; k++) {
						strcpy(name2[k2], name[k]);
						phi2[k2] = phi[k];
						mat2[k2] = mat[k];
						inf2[k2] = inf[k];
						k2++;
					}
					for (k = del + 1; k <= max2; k++) {
						strcpy(name2[k2], name[k]);
						phi2[k2] = phi[k];
						mat2[k2] = mat[k];
						inf2[k2] = inf[k];
						k2++;
					}
				}
				else {
					printf("������ ������ � ������ ���.\n");
					go = 0;
				}
			} while (go == 0);
			k2 = 0;
			for (k = 0; k < max2; k++) {
				fwrite(&name[k], sizeof(name[k]), 1, f);
				fwrite(&phi[k], sizeof(int), 1, f);
				fwrite(&mat[k], sizeof(int), 1, f);
				fwrite(&inf[k], sizeof(int), 1, f);
				strcpy(name[k], name2[k2]);
				phi[k] = phi2[k2];
				mat[k] = mat2[k2];
				inf[k] = inf2[k2];
				k2++;
			}
			max2--;

			fclose(f);
			num = 1;
			lc = 0;
			list = 1;
			break;

		}
		case 3: {
			//�������� ������.
			f = fopen(filename, "wb");

			do {
				k2 = 0;
				go = 1;
				printf("������� ����� ��������: ");
				scanf("%i", &del);
				del--;
				if (del <= max2 && del >= 0) {
					printf("%s\n������: %i\t����������: %i\t�����������: %i\n", name[del], phi[del], mat[del], inf[del]);
					printf("������� ����� ������: ");
					printf("\n������: ");
					scanf("%i", &phi[del]);
					printf("\n����������: ");
					scanf("%i", &mat[del]);
					printf("\n�����������: ");
					scanf("%i", &inf[del]);

					//���� ������ � ����.
					for (k = 0; k <= max2; k++) {
						fwrite(&name[k], sizeof(name[k]), 1, f);
						fwrite(&phi[k], sizeof(int), 1, f);
						fwrite(&mat[k], sizeof(int), 1, f);
						fwrite(&inf[k], sizeof(int), 1, f);
					}
				}
				else {
					printf("������ ������ � ������ ���.\n\n");
					go = 0;
				}
			} while (go == 0);

			fclose(f);
			num = 1;
			lc = 0;
			list = 1;
			break;

		}
		case 4: {
			//���-�� ����� �� ������� ��������.
			system("cls");

			for (k = 0; k <= max2; k++) {
				if (phi[k] == 2) {
					phic++;
				}
				if (mat[k] == 2) {
					matc++;
				}
				if (inf[k] == 2) {
					infc++;
				}
			}
			printf("���������� �����: \n�� ������: %i\t�� ����������: %i\t�� �����������: %i\n\n\n", phic, matc, infc);
			system("pause");
			phic = 0;
			matc = 0;
			infc = 0;
			num = 1;
			lc = 0;
			list = 1;
			break;
		}
		case 5: {
			//�������� � ��������.
			system("cls");

			printf("�������� � ���� �� ����� �������: \n");
			for (k = 0; k <= max2; k++) {
				if (phi[k] == 2 || mat[k] == 2 || inf[k] == 2) {
					if (phi[k] == 2) {
						cd++;
					}
					if (mat[k] == 2) {
						cd++;
					}
					if (inf[k] == 2) {
						cd++;
					}
					printf("%s\t\t���������� �����: %d\n", name[k], cd);
					cd = 0;
				}
			}

			num = 1;
			lc = 0;
			list = 1;
			system("pause");
			break;
		}
		case 6: {
			if (list < maxlc) {
				num = list * 5 + 1;
				list++;
				lc = k;
			}
			else {
				num = list * 5 - 4;
				lc -= 1 + (max2 - k) % 5;
				printf("\n��� ��������� ��������\n\n");
				system("pause");
			}

			break;
		}
		case 7: {
			if (list > 1) {
				list--;
				num = list * 5 - 4;
				if (k % 5 != 0) {
					lc -= 6 + (max2 - k) % 5;
				}
				else {
					lc = k - 10;
				}
			}
			else {
				num -= 5;
				printf("\n��� ������ ��������\n\n");
				system("pause");
			}

			break;
		}
		case 8:
			go2 = 1;
			break;
		default:
			printf("�������� ������������ ����� ����.\n");
			system("pause");
			num -= 5;
			lc = k - 5;
		}
	} while (go2 == 0);


	return 0;
}