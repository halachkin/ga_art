fmax=0;

for i=1:10000
    x=GENERUJ(1,-1000,1000);
    f=funkce(x);
    if f>fmax
        xmax=x;
        fmax=f;
    end
end
fmax
xmax