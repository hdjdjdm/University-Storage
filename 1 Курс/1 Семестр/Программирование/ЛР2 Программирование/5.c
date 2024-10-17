#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	int n, x = 5;
	printf("n = ");
	scanf("%d", &n);
	while (x < n)
		x = x * 5;
	if (x == n)
		printf("Yes\n");
	else
		printf("No\n");
	system("pause");
	return 0;
}
//n=7 res=No
//n=25 res=Yes
