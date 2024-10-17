function S = F(x)
if mod(x, 3)==0
    S = strcat(num2str(x), ' Кратно трем');
else
    S = strcat(num2str(x), ' Не кратно трем');
end;