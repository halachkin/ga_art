fmax=0;
j=1;
N=1000000;
h=waitbar(0,strcat('Spocteno: 0/ ',num2str(N)));
for i=1:N
    x=GENERUJ(1,-1000,1000);
    f=funkce(x);
    if f>fmax
        xmax=x;
        fmax=f;
    end
    j=j+1;
    if (j>10000)
        j=1;
        waitbar(i/N,h,strcat('Spocteno: ',num2str(i),'/ ',num2str(N)));
    end
    
end
waitbar(1,h,strcat('Spocteno: ',num2str(N),'/ ',num2str(N)));
fmax
xmax