#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	int n, s;
	float x, y;
	printf("n = ");
	scanf("%i", &n);
	printf("x = ");
	scanf("%f", &x);

	y = sin(x);

	for (s = 1; s < n; s++)
	{
		if (s % 2 == 0)
			y += cos(y);
		else
			y += sin(y);
	}
	printf("%f\n", y);
	system("pause");
	return 0;
}
//n=4 x=5 res=-2.899079
//n=314 x=228 res=2.832499
