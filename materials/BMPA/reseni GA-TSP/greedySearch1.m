%najdi nejkratsi vzdalenost mezi dvema mesty, jedno z mest vyber jako
%vychozi a z neho najdi nejblizsi dosud nenavstivene mesto atd.

load('mesta.txt');
pocet_mest=length(mesta(:,1));

%MATICE VZDALENOSTI
for i=1:pocet_mest
    for j=1:pocet_mest
        if (i~=j) %vzdalenosti pod i nad diagonalou
            deltax=mesta(i,2)-mesta(j,2);
            deltay=mesta(i,3)-mesta(j,3);
            vzd(i,j)=(deltax^2+deltay^2)^0.5;
            vzd(j,i)=(deltax^2+deltay^2)^0.5; %i symetricke hodnoty
        else %same +INF
            vzd(i,j)=Inf;
        end
    end
end 
            
%NAJDI VYCHOZI BOD PODLE NEJKRATSI VZDALENOSTI
minimum=Inf;
for i=1:(pocet_mest-1)
    for j=(i+1):pocet_mest
        if minimum>vzd(i,j)
            minimum=vzd(i,j);
            reseni(1)=i; %vychozi bod, ze ktereho vede nejkratsi cesta
        end
    end
end

%ZMENOU VYCHOZIHO MESTA NA NAHODNE LZE NALEZTI JINA RESENI
%reseni(1)=45;

%GREEDY SEARCH
for cest=2:pocet_mest
    %najdi minimum z mesta cest-1
    minimum=Inf;
    for i=1:pocet_mest %projdi cely sloupec
        if (minimum>vzd(i,reseni(cest-1)))
            minimum=vzd(i,reseni(cest-1));
            reseni(cest)=i;
        end
    end
    %zajisti, ze uz nikdo do mesta cest-1 nepujde
     for i=1:pocet_mest
         vzd(i,reseni(cest-1))=Inf;
         vzd(reseni(cest-1),i)=Inf;
     end
end
    
figure('Name','GreedySearch');
hold on;
plot(mesta(reseni,2),mesta(reseni,3));
plot([mesta(reseni(pocet_mest),2),mesta(reseni(1),2)],[mesta(reseni(pocet_mest),3),mesta(reseni(1),3)]);
        
-VYHODNOCENI(reseni,mesta)