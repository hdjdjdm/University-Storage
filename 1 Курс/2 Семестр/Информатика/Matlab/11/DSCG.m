function y = DSCG(CH, G);
CD = double(CH);
G1 = double(G);
D = mod(CD - G1 - 6 + 1104, 1104);
y = D;
y;