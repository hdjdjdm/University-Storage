#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	float x;
	float exp = expf(1);
	printf("x = ");
	scanf("%f", &x);
	if (x > 1)
	{
		float S = (sqrt(fabs(pow(log10(1 / tan(x)), 2) - (pow(3 * x, 1 / 4) / cos(x))) + sqrt(1 / 2 * x) + 1)) / (pow(exp, -3 * x) + pow(exp, atan(x)));
		printf("%f\n", S);
	}
	system("pause");
	return 0;
}
//x=4 res=0.422768