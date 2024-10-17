function [P, V] = F2(x, y)
if x<=0 && y<=0
    P = x^3;
    V = y^3;
elseif x<=0 || y<=0
    P = x*2;
    V = y*2;
else 
    P = x/2; 
    V = y/2;
end;
[P, V]