function potomek=OrderCrossover(r1,r2)
potomek=r1;
od=floor(rand*(length(r1)-2)+1); %1 az delka-2
do=od+floor(rand*(length(r1)-od)+1); %do
for i=od:do %vynuluj z r1 do potomka zkopirovane prvky
    r1(i)=0;
end
ir1=find(r1); %indexy nenulovych prvku v r1, tedy volna mista v potomkovi
for i=1:length(r1) %vymaz z r2 jiz pouzita mesta v r1
    if (r1(i)==0) %v r1 nula, tedy je preneseno do potomka
        r2(find(r2==potomek(i)))=0; %to cislo vynuluj v r2, nuly v pouzitych mestech
    end
end
ir2=find(r2>0);

potomek(ir1)=r2(ir2);

end