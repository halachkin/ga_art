% funkce VYHODNOCENI REALNE vraci vektor obsahujici fitness jednotlivych jedincu
% vyhodceni je HODNOTA funkce, vstupy od -1000 do 1000
% IN: vektor populace(N,2)
% OUT: vektor fitness(N)

function out=VYHODNOCENI(populace,mesta)

Npop=length(populace(:,1));
Nmest=length(populace(1,:));


for i=1:Npop
    trasa=0;
    for j=1:Nmest-1
        deltax=mesta(populace(i,j),2)-mesta(populace(i,j+1),2);
        deltay=mesta(populace(i,j),3)-mesta(populace(i,j+1),3);
        trasa=trasa+(deltax^2+deltay^2)^0.5;
    end
    deltax=mesta(populace(i,1),2)-mesta(populace(i,Nmest),2);
    deltay=mesta(populace(i,1),3)-mesta(populace(i,Nmest),3);
    trasa=trasa+(deltax^2+deltay^2)^0.5;
    out(i)=-trasa;
end