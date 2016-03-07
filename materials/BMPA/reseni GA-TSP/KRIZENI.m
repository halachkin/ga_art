% KRIZENI - dostane matici R rodicu, vrati R/2 rodicu {zaokrouhleno dolu)
% IN:
%   prav - pravdepodobnost krizeni, jinak jdou dal oba rodice
%   typ 1,2,3
% OUT: generace krizenych bastardu

function out=KRIZENI(rodice)

for i=1:2:(length(rodice(:,1))-1)
    out(i,:)=OrderCrossover(rodice(i,:),rodice(i+1,:));
    out(i+1,:)=OrderCrossover(rodice(i+1,:),rodice(i,:));
end
    
end

