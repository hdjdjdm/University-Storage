/*
3. Метод прямоугольников.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <locale.h>

//Подинтегральное выражение.
float integ(float x, int ch) {
    if (ch == 1) {
        return (float)(2 * x + pow(x, 2));
    }
    else if (ch == 0) {
        return (float)(4 * pow(cos(x), 2));
    }
    else {
    return 0;
    }
}

//Интеграл.
float Integral(float a, float b, int c) {
    int n = 30;
    float h = (b - a) / n, S = 0;
    for (int i = 0; i < n; i++) {
        S += integ(a + h * (i + 0.5), c);
    }
    S *= h;
    return S;
}


int main() {

    setlocale(LC_ALL, "Russian");

    bool run;
    int choise;
    double S, x;

    printf("Выберите подинтегральное выражение с его пределами: \n1. 2*x + x^2\t\tНижний предел интеграла = -2\tВерхний предел интеграла = 2\n2. 4 * cos^2(x)\t\tНижний предел интеграла = 0\tВерхний предел интеграла = 0.5\n");

    //Выбор подинтегральной функции.
    do {
        run = 1;
        scanf("%i", &choise);
        switch (choise) {
        case 1:
            S = Integral(-2, 2, 1);
            break;
        case 2:
            S = Integral(0, 0.5, 0);
            break;
        default:
	    printf("Введите 1 или 2: ");
            run = 0;
        }
    } while (run == 0);

    //Ответ.
    printf("\nИнтеграл = %.2f\n", S);

    system("pause");
    return 0;
}
