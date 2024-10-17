#include <stdio.h>
#include <stdlib.h>

int main() {
	int c = 5, d;
	double a = 5, b;
	printf("b=");
	scanf("%lf", &b);
	printf("d=");
	scanf("%d", &d);
	a += b - 2;
	printf("a = a + b - 2 : a=%.2lf b=%.2lf c=%i d=%i\n", a, b, c, d);
	c += 1, d += c - a;
	printf("c=c+1, d=c-a+d : a=%.2lf, b=%.2lf c=%i, d=%i\n", a, b, c, d);
	a *= c, c -= 1;
	printf("a=a*c, c=c-1 : a=%.2lf, b=%.2lf, c=%i, d=%i\n", a, b, c, d);
	a /= 10, c /= 2, b -= 1, d *= (c + b + a);
	printf("a=a/10, c=c/2, b=b-1, d=d*(c+b+a) : a=%.2lf b=%.2lf, c=%i, d=%i\n", a, b, c, d);
	system("pause");
	return 0;
}
