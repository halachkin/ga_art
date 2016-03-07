load('mesta.txt');
mesta=mesta(1:20,:)
pocet_mest=length(mesta(:,1));

trasa(pocet_mest, pocet_mest)=0;

%MATICE VZDALENOSTI
for i=1:pocet_mest
    for j=1:pocet_mest
        if (i<j) %vzdalenosti
            deltax=mesta(i,2)-mesta(j,2);
            deltay=mesta(i,3)-mesta(j,3);
            vzd(i,j)=(deltax^2+deltay^2)^0.5;
        else %same +INF
            vzd(i,j)=Inf;
        end
    end
end 
            
%MATICE POUZITYCH MEST, zapisuje se i pod diagonalou (i,j) a (j,i)
for i=1:pocet_mest
    for j=1:pocet_mest
        trasa(i,j)=0;
    end
end


%GREEDY SEARCH
for cest=1:pocet_mest
    %najdi minimum
    minimum=Inf;
    for i=1:(pocet_mest-1)
        for j=(i+1):pocet_mest
            if minimum>vzd(i,j)
                minimum=vzd(i,j);
                i_min=i;
                j_min=j;
            end
        end
    end
    
    %vzd(i_min,j_min)=Inf;
    vzd(i_min,j_min)=Inf;
    
    
    %pridej to trasa
    trasa(i_min,j_min)=1;
    trasa(j_min,i_min)=1; %symetricky zapsano i pod hlavni diagonalu

    %je-li suma pouziteho mesta=2, vzdalenosti na Inf
    if (sum(trasa(i_min,:))==2) %jiz vedou dve cesty
        vzd(i_min,:)=Inf; %vsechny v radku prepsany na Inf
        vzd(:,i_min)=Inf; %vsechny v radku prepsany na Inf
    end
    if (sum(trasa(j_min,:))==2) %jiz vedou dve cesty
        vzd(j_min,:)=Inf; %vsechny v radku prepsany na Inf
        vzd(:,j_min)=Inf; %vsechny v radku prepsany na Inf
    end
end

trasa

%VEKTOR PORADI MEST
from=1;%vychozi mesto
reseni(1)=from;
pocet_mest
for i=1:(pocet_mest-1)
    for to=1:pocet_mest %hledani dalsiho mesta
        if(trasa(from,to)==1)
            reseni(i+1)=to;
            trasa(from,to)=0;
            trasa(to,from)=0;
            from=to;
            break;
        end
    end

end
    
figure;
hold on;
plot(mesta(reseni,2),mesta(reseni,3));
%plot(mesta([populace(index,1),populace(index,50)],2),mesta([populace(index,1),populace(index,50)],3));

        
-VYHODNOCENI(reseni,mesta)