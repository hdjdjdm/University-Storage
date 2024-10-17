#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int n = 20;
    double x, result=0;

    printf("x = ");
    scanf("%lf", &x);
    if (pow(x, 2) < 1)
        exit;
    else
    {
        printf("Error\n");
	system("pause");
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        result += (pow(-1, i) * pow(x, 2 * i + 1)) / (2 * i + 1);
    }

    printf("%lf\n", result);
    printf("%lf\n", atan(x));

    system("pause");
    return 0;
}
/*
0.25
0.244979
0.244979
*/
