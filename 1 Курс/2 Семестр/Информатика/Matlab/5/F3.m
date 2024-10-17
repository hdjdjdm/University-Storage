function T=F3(x)
a = -3;
b = 0.3;
T=exp(b.*x).*sin(a.*x+b)-sqrt(abs(b.*x+a)) - a.*sin(x);