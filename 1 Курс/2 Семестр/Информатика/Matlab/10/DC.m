function [Y] = DC(X)
for i = 1:5
    Y(i,1) = X(i,3) | X(i,2) | not(X(i,1));
    Y(i,2) = X(i,3) | not(X(i,2)) | X(i,1);
    Y(i,3) = not(X(i,3)) | X(i,2) | X(i,1);
    Y(i,4) = not(X(i,3)) | X(i,2) | not(X(i,1));
    Y(i,5) = not(X(i,3)) | not(X(i,2)) | not(X(i,1));
end;
Y;