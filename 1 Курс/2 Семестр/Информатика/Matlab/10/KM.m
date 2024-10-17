function [Z] = KM(Y,D)
for i = 1:5
    Z(i) = (Y(i,1)|D(i,1)) & (Y(i,2)|D(i,2)) & (Y(i,3)|D(i,3)) & (Y(i,4)|D(i,4)) & (Y(i,5)|D(i,5));
end
Z;