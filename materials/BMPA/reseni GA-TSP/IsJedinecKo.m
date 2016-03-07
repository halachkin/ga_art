function out=IsJedinecKo(matice_jedincu)

for i=1:length(matice_jedincu(:,1)) %pres vsechny jedince, pocet radku
    for j=1:length(matice_jedincu(1,:)) %vsechna mesta v i-tem jedinci
        if (find(matice_jedincu(i,:)==j))
            out(i)=0;
        else
            out(i)=1;
            break;
        end
    end
end
