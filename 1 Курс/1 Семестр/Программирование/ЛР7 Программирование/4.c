/*
4. Результаты сдачи студентами экзаменационной сессии хранятся в
файле, содержащем следующие данные: фамилия студента и оценки по
физике, математике и информатике. Вывести количество двоек по каждому из
предметов и вывести список студентов, имеющих двойки хотя бы по одному
предмету.

Повышенный уровень.
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

//Вывод линии.
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

	printf("Добро пожаловать в базу данных ПГУТИ!\n\n");
	printf("Выберите один из вариантов: \n1.Создать новый файл.\n2.Открыть существующий файл с возможностью редактирования.\n");
	do {
		scanf("%d", &choice);
		switch (choice) {
		case 1: {
			//Создание файла.
			if (argc != 2) {
				do {
					printf("Введите имя файла: ");
					scanf("%s", filename);
					f = fopen(filename, "wb");
				} while (f == NULL);
			}
			else {
				strcpy(filename, argv[1]);
				f = fopen(filename, "wb");
				if (f == NULL) {
					printf("Не удается открыть файл.\n");
					do {
						printf("Введите имя файла: ");
						scanf("%s", filename);
						f = fopen(filename, "wb");
					} while (f == NULL);
				}
			}

			//Ввод данных о студентах.
			do {
				printf("Введите фамилию студента: ");
				scanf("%s", name[k]);
				printf("Введите его оценки по физике, математике и информатике: \n");
				scanf("%d %d %d", &phi[k], &mat[k], &inf[k]);

				do {
					go = 1;
					printf("Добавить еще студента?\n1.Да\n2.Нет\n");
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


			//Ввод данных в файл.
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
			//Открытие файла.
			if (argc != 2) {
				do {
					printf("Введите имя файла: ");
					scanf("%s", filename);
					f = fopen(filename, "rb");
				} while (f == NULL);
			}
			else {
				strcpy(filename, argv[1]);
				f = fopen(filename, "rb");
				if (f == NULL) {
					printf("Не удается открыть файл.\n");
					do {
						printf("Введите имя файла: ");
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
			printf("Выберите существующий пункт меню.\n");
			go = 0;
		}
	} while (go == 0);



	int max2 = max, go2 = 0, del, k2 = 0, phic = 0, matc = 0, infc = 0, list = 1, lc = 0, maxlc;
	do {
		max = max2;
		maxlc = max2 / 5 + 1;
		//Таблица.
		system("cls");
		if (list > 1 && list < maxlc) {
			printf("%51s %d >>\n", " << Страница", list);
		}
		else if (list == 1) {
			printf("%51s %d >>\n", "Страница", list);
		}
		else if (list == maxlc) {
			printf("%51s %d\n", " << Страница", list);
		}

		line();
		printf("|  №  |        Фамилия студента        |    Физика    |    Математика    |    Информатика    |\n");
		line();

		for (k = lc; k < list * 5 && k <= max2; k++) {
			printf("|%5d|%32s|%14d|%18d|%19d|\n", num++, name[k], phi[k], mat[k], inf[k]);
			line();
		}

		printf("\n\nРабота с файлом:\n1.Добавить студентов.\n2.Удалить студента.\n3.Изменить данные.\n\
4.Вывести количество двоек по каждому из предметов.\n5.Вывести список студентов, имеющих двойки хотя бы по одному предмету.\n6.Вперед>>\n7.Назад<<\n8.Закрыть программу\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1: {
			//Добавление в файл новых данных.
			f = fopen(filename, "ab");

			k = max2;
			do {
				k++;
				max2++;
				printf("Введите фамилию студента: ");
				scanf("%s", name[k]);
				printf("Введите его оценки по физике, математике и информатике: \n");
				scanf("%d %d %d", &phi[k], &mat[k], &inf[k]);

				do {
					go = 1;
					printf("Добавить еще студента?\n1.Да\n2.Нет\n");
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

			//Ввод данных в файл.
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
			//Удаление студентов.
			f = fopen(filename, "wb");

			do {
				k2 = 0;
				go = 1;
				printf("Введите номер студента: ");
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
					printf("Такого номера в списке нет.\n");
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
			//Поменять оценки.
			f = fopen(filename, "wb");

			do {
				k2 = 0;
				go = 1;
				printf("Введите номер студента: ");
				scanf("%i", &del);
				del--;
				if (del <= max2 && del >= 0) {
					printf("%s\nФизика: %i\tМатематика: %i\tИнформатика: %i\n", name[del], phi[del], mat[del], inf[del]);
					printf("Введите новые оценки: ");
					printf("\nФизика: ");
					scanf("%i", &phi[del]);
					printf("\nМатематика: ");
					scanf("%i", &mat[del]);
					printf("\nИнформатика: ");
					scanf("%i", &inf[del]);

					//Ввод данных в файл.
					for (k = 0; k <= max2; k++) {
						fwrite(&name[k], sizeof(name[k]), 1, f);
						fwrite(&phi[k], sizeof(int), 1, f);
						fwrite(&mat[k], sizeof(int), 1, f);
						fwrite(&inf[k], sizeof(int), 1, f);
					}
				}
				else {
					printf("Такого номера в списке нет.\n\n");
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
			//Кол-во двоек по каждому предмету.
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
			printf("Количество двоек: \nПо физике: %i\tПо математике: %i\tПо информатике: %i\n\n\n", phic, matc, infc);
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
			//Студенты с двойками.
			system("cls");

			printf("Студенты с хотя бы одной двойкой: \n");
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
					printf("%s\t\tКоличество двоек: %d\n", name[k], cd);
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
				printf("\nЭто последняя страница\n\n");
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
				printf("\nЭто первая страница\n\n");
				system("pause");
			}

			break;
		}
		case 8:
			go2 = 1;
			break;
		default:
			printf("Выберите существующий пункт меню.\n");
			system("pause");
			num -= 5;
			lc = k - 5;
		}
	} while (go2 == 0);


	return 0;
}