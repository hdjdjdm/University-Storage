#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	int x, a, b, c;
	printf("x = ");
	scanf("%d", &x);
	a = x / 100;
	b = (x / 10) % 10;
	c = x % 10;
	if (a == b && a == c && b == c)
	{
		a--;
		if (c != 9)
			c++;
		x = a * 100 + b * 10 + c;
		printf("%d", x);
		return 0;
	}
	if ((a == b && (a != c || b != c)) || (a == c && (a != b || c != b)) || (b == c && (a != b || a != c)))
		x = c * 100 + b * 10 + a;
	printf("%d\n", x);
	system("pause");
	return 0;
}
//x=228 res=822
//x=666 res=567
//x=123 res=123
//x=999 res=899