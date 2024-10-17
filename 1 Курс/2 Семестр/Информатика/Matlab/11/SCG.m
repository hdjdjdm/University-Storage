function y = SCG(S, G);
C = double(S);
G1 = double(G);
CK = mod(C + 6 + G1, 1104);
y = CK;
y;