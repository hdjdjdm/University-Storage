#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	float t, s;
	printf("t = ");
	scanf("%f", &t);
	printf("s = ");
	scanf("%f", &s);
	if (t >= s && 2 < s && s <= 4)
		printf("%.2f", pow(t - s, 1 / 4));
	else if (t < 0)
		printf("%.2f", pow(s, 4) + 2 * t);
	else
		printf("%.2f\n", t + 2);
	system("pause");
	return 0;
	// t=-4 s=2 res=8
	// t=2 s=5 res=4
}
