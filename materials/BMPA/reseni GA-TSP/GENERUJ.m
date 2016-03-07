% poradi 100 mest
% IN: pocet jedincu, ktery bude vygenerovan
% OUT: matici[pocet,6], v rozsahu xMIN az xMAX

function out=GENERUJ(pocet,Nmest)

for i=1:pocet
    for j=1:Nmest
        mest(j)=j;
        nah(j)=rand;
    end
    [Y,I]=sort(nah); %usporadej nahodne
    mest=mest(I); %podle serazenych nahodnych usporadej mesta
    out(i,:)=mest; %vytvor jedince do out
end
