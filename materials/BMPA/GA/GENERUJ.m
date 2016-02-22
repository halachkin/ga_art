% funkce generuje <pocet > 6-tic realnych cisel v rozmezi -1000 az 1000
% IN: pocet jedincu, ktery bude vygenerovan
% OUT: matici[pocet,6], v rozsahu xMIN az xMAX

function out=GENERUJ(pocet,xMIN,xMAX)

for i=1:pocet
   out(i,1)=rand*(xMAX-xMIN)+xMIN;
   out(i,2)=rand*(xMAX-xMIN)+xMIN;
   out(i,3)=rand*(xMAX-xMIN)+xMIN;
   out(i,4)=rand*(xMAX-xMIN)+xMIN;
   out(i,5)=rand*(xMAX-xMIN)+xMIN;
   out(i,6)=rand*(xMAX-xMIN)+xMIN;
end
