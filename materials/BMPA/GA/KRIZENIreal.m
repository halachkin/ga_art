% KRIZENI REALNE kodovanych genu
% IN:
%   prav - pravdepodobnost krizeni, jinak jdou dal oba rodice
%   typ 1,2,3 - vyber jeden a naprogramuj
% OUT: generace krizenych jedincu

function out=KRIZENIreal(prav,gen,xMIN,xMAX)

if(prav>rand)
    P1 = (gen + gen)./2;
    P2 = (3*gen - gen)./2;
    P3 = (-gen + 3*gen)./2;
    P1(P1>xMAX) = xMAX;
    P2(P1>xMAX) = xMAX;
    P3(P1>xMAX) = xMAX;
    P1(P1<xMIN) = xMIN;
    P2(P1<xMIN) = xMIN;
    P3(P1<xMIN) = xMIN;
    fit1 = mean(VYHODNOCENI(P1));
    fit2 = mean(VYHODNOCENI(P2));
    fit3 = mean(VYHODNOCENI(P3));
    [m i] = min([fit1 fit2 fit3]);
    switch i
        case 1
            out = [P2 ; P3];
            return;
        case 2
            out = [P1 ; P3];
            return;
        case 3
            out = [P1 ; P2];
            return      
    end
else
    out = [];
end
