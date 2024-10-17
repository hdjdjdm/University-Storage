#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int fact(int num)
{
    int fact = 1;
    for (int i = 1; i <= num; ++i)
    {
        fact *= i;
    }
    return fact;
}

int main() {
    int n = 6;
    double x, result=0;

    printf("x = ");
    scanf("%lf", &x);
    if (x >= 0.1 && x <= 1)
    {
        exit;
    }
    else
    {
        printf("Error\n");
	system("pause");
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        result += pow(x, 2 * i) / fact(2 * i);
    }

    printf("%lf\n", result);
    printf("%lf\n", (exp(x) + exp(-x)) / 2);
    system("pause");
    return 0;
}
/*
0.2
1.020067
1.020067
*/

