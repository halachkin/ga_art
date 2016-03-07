
% IN:
% prav - pravdepodobnost mutace

function out=MUTACE(pM,potomci)

Npot=length(potomci(:,1));
Nmest=length(potomci(1,:));

for i=1:Npot
   if (rand<pM)
       j1=floor(rand*Nmest*0.999)+1;
       j2=floor(rand*Nmest*0.999)+1;
       pom=potomci(i,j1);
       potomci(i,j1)=potomci(i,j2);
       potomci(i,j2)=pom;
   end
   out=potomci;
end