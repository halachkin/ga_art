clear;
		% model, ktery hleda extrem funkce "funcke([1 2 3 4 5 6])"

		% interval reseni a nazev je treba nastavit v souboru VYHODNOCENI a START

		%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		% NASTAVITELNE PARAMETRY
elit=1; 	% nastaveni elitismu
pM=0.9;   	% pravdepodobnost mutace
populace_velikost=60;    	% velikost populace
G=1000;   	% pocet generaci v ukoncovaci podmince
		%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

load('mesta.txt');
pocet_mest=length(mesta(:,1));

		% 1. vygeneruj prvni populaci
populace=GENERUJ(populace_velikost, pocet_mest); 	% populace je matice vektrou
fitness=VYHODNOCENI(populace,mesta);

generace=0;
	fitmean(1)=mean(fitness);fitmax(1)=max(fitness); % pro ucely vykresleni grafu


while (generace<G)

    elita=ELITISMUS(elit,populace,fitness);
    selekce=SELEKCE(round(populace_velikost/2),populace,fitness);
    krizeni=KRIZENI(selekce);
    mutace=MUTACE(pM,krizeni);
    novagen=[mutace;elita;selekce];
    
      clear fitness;
    fitness=VYHODNOCENI(novagen,mesta);
      clear populace;
    populace=novagen;
      clear elita selekce krizeni mutace novagen;
    generace=generace+1;
    
    fitmean(generace+1)=mean(fitness);fitmax(generace+1)=max(fitness);
    waitbar(generace/G);
end



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% PRUBEH K ZISKANI NEJLEPSIHO JEDINCE

[fxy index]=max(fitness);
-fxy
populace(index,:)';

figure('Name','GA-TSP-fitness');
%hold on;grid on;
title( ['NALEZENO: ','Max f(x,y)=',num2str(-max(fitness))] );
xlabel('Pocet generací');
ylabel('Hodnotící funkce');

plot(0:generace,-fitmean,'b-');
plot(0:generace,-fitmax,'k-');

figure('Name','GA-TSP');
hold on;
plot(mesta(populace(index,:),2),mesta(populace(index,:),3));
plot(mesta([populace(index,1),populace(index,50)],2),mesta([populace(index,1),populace(index,50)],3));


