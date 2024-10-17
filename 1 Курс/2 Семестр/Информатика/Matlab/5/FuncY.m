N = (xmax - xmin) / h;
X = xmin:h:xmax;
for  n=1:N+1
    if X(n)<0 Y(n)=sin(b*X(n)^2);
    elseif X(n)>3 Y(n)=X(n)*cos(X(n))^3;
    else Y(n)=0; end;
    end
figure(1);
plot(X,Y,'r');
title('X-Y');
grid on;