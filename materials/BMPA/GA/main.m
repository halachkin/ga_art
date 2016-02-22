clc;
clear all;
		% model, ktery hleda extrem funkce "funcke([1 2 3 4 5 6])"

		% interval reseni a nazev je treba nastavit v souboru VYHODNOCENI a START

		%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		% NASTAVITELNE PARAMETRY
elit=5; 	% nastaveni elitismu
pK=0.8; 	% pravdepodobnost krizeni
pM=0.05;   	% pravdepodobnost mutace
N=100;    % velikost populace
G=1000;   	% pocet generaci v ukoncovaci podmince
xMAX=1000; 	% maximalni hodnota x
xMIN=-1000;	% minimalni ho dnota x
		%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


		% 1. vygeneruj prvni populaci
		% VYHODNOCENI (pouzije se v selekci...)
		% CYKLUS
		%   SELEKCE
		%   KRIZENI
		%   MUTACE
		%   VYHODNOCENI
		%   UKONCOVACI PODMINKA
		% END


		% 1. vygeneruj prvni populaci
populace=GENERUJ(N,xMIN,xMAX); 	% populace je matice vektrou x (co radek to x=[x1,x2,...,x6])
fitness=VYHODNOCENI(populace);

generace=0;
	fitmean(1)=mean(fitness);fitmax(1)=max(fitness); % pro ucely vykresleni grafu




while (generace<G)

    elita=ELITISMUS(elit,populace,fitness); %elita je matice s nakopirovanym nejlepsim jedincem
    selekce=SELEKCE(round(N/2),populace,fitness); %selekce je matice jedincu prezivsich selekci
    krizeni=KRIZENIreal(pK,selekce,xMIN,xMAX); %krizeni je matice jedincu - potomku po krizeni
    mutace=MUTACEreal(pM,generace,G,krizeni,xMIN,xMAX); %mutace je matice jedincu - potomku po mutaci
    novagen=[mutace;elita;selekce]; %nova generace z: potomku po mutaci, elity, rodicu (prezili selekci)
    
      clear fitness;
    fitness=VYHODNOCENI(novagen);
      clear populace;
    populace=novagen;
      clear elita selekcen krizeni mutace novagen;
    generace=generace+1
    
    fitmean(generace+1)=mean(fitness); fitmax(generace+1)=max(fitness);
end



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% PRUBEH K ZISKANI NEJLEPSIHO JEDINCE

[fxy index]=max(fitness);

x1=populace(index,1);
x2=populace(index,2);
x3=populace(index,3);
x4=populace(index,4);
x5=populace(index,5);
x6=populace(index,6);

disp(['Max f(x,y)= ' num2str( max(fitness) )]);
disp(['x1= ' num2str(x1)]);
disp(['x2= ' num2str(x2)]);
disp(['x3= ' num2str(x3)]);
disp(['x4= ' num2str(x4)]);
disp(['x5= ' num2str(x5)]);
disp(['x6= ' num2str(x6)]);

hold on;grid on;
title( ['NALEZENO: ','Max f(x,y)=',num2str(max(fitness))] );
xlabel('Pocet generací');
ylabel('Hodnotící funkce');
plot(0:generace,fitmean,0:generace,fitmax)
% plot(0:generace,fitmax,'k-');
figure(2)
plot(fitness)


