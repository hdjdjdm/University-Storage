function Y=F1(x)
b = 0.3;
a = -3;
Y=exp(b.*x).*sin(a.*x+b)-sqrt(abs(b.*x+a));