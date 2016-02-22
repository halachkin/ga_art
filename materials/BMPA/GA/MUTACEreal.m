% IN:
% prav - pravdepodobnost mutace

function out=MUTACEreal(prav,generace,G,krizeni,xMIN,xMAX)

for i = 1:length(krizeni)
    if(prav>rand)
        randomi1 = round(rand*(size(krizeni,2) - 1) + 1);
        t = krizeni(i,randomi1);
        randomi2 = round(rand*(size(krizeni,2) - 1) + 1);
        krizeni(i,randomi1) = krizeni(i,randomi2);
        krizeni(i,randomi2) = t;
    end  
end    
out = krizeni;