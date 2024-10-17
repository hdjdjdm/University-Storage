#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	int n = 1, k;
	printf("k = ")
	scanf("%i", &k);
	for (int x = 2; x <= 8; x++)
	{
		while (pow(x, n) <= k)
		{
			n++;
		}
		printf("for %i  n = %i\n", x, n);
		n = 1;
	}
	system("pause");
	return 0;
}
// k = 666
//for 2 n = 10
//for 3 n = 6
//for 4 n = 5
//for 5 n = 5
//for 6 n = 4
//for 7 n = 4
//for 8 n = 4