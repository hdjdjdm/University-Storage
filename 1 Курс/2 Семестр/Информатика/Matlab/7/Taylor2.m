Y = [0, 0, 0];
n = 0;
a = x;
s = a;
while abs(a) > E
    Y = [a, s, n];
    n = n + 1;
    a = (-1)^n * x^(2*n+1) / factorial(2*n + 1);
    s = s+a;
    Y
    C = strcat(num2str(n), ' Членов')
end;
