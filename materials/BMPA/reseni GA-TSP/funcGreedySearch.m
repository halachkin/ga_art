function out=funcGreedySearch(mesta)
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
vzd_ini=vzd;

for k=1:pocet_mest
    vzd=vzd_ini;
    
    reseni(1)=k;

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
    
    out(k,:)=reseni;
end