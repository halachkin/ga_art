% funkce VYHODNOCENI REALNE vraci vektor obsahujici fitness jednotlivych jedincu
% vyhodceni je HODNOTA funkce, vstupy od -1000 do 1000
% IN: vektor populace(N,2)
% OUT: vektor fitness(N)

function out=VYHODNOCENI(populace)

for i=1:length(populace(:,1))
    out(i)=funkce([populace(i,1) populace(i,2) populace(i,3) ...
                   populace(i,4) populace(i,5) populace(i,6)]); % fitness jednotlivych prvku
end