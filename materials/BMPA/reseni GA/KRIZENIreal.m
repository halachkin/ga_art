% KRIZENI REALNE kodovanych genu
% IN:
%   prav - pravdepodobnost krizeni, jinak jdou dal oba rodice
%   typ 1,2,3
% OUT: generace krizenych bastardu

function out=KRIZENIreal(prav,gen,xMIN,xMAX)
vstupu=6;


% zjisti, jestli ke krizeni dojde
for i=1:2:(length(gen(:,1))-1)
  if (prav<rand)
       out(i:(i+1),:)=gen(i:(i+1),:);
       continue;
  end
  
  potomci(1,:)=(gen(i,:)+gen(i+1,:))/2;  
  potomci(2,:)=(3*gen(i,:)-gen(i+1,:))/2;
  potomci(3,:)=(-gen(i,:)+3*gen(i+1,:))/2;

  for ii=1:length(potomci(:,1))
     for j=1:vstupu
       %if (potomci(ii,j)>xMAX) potomci(ii,j)=2*xMAX-potomci(ii,j);end
       if (potomci(ii,j)>xMAX) potomci(ii,j)=xMAX;end
       %if (potomci(ii,j)<xMIN) potomci(ii,j)=2*xMIN+potomci(ii,j);end       
       if (potomci(ii,j)<xMIN) potomci(ii,j)=xMIN;end
     end
   end  
  
  kvalita=VYHODNOCENI(potomci);
  [ser index]=sort(kvalita);
  out(i,:)=potomci(index(3),:);
  out(i+1,:)=potomci(index(2),:);

  
   for ii=1:length(out(:,1))
     for j=1:vstupu
       if (out(ii,j)>xMAX) out(ii,j)=2*xMAX-out(ii,j);end
       if (out(ii,j)<xMIN) out(ii,j)=2*xMIN+out(ii,j);end       
     end
   end
end