% IN:
% prav - pravdepodobnost mutace

function out=MUTACEreal(prav,generace,G,krizeni,xMIN,xMAX)

vstupu=6;
out=krizeni;

  % dynamicka mutace Michalewicz
    for i=1:length(out(:,1))
       for j=1:length(out(1,:))
           if (rand<prav)
               if (rand<0.5)
                   x = xMAX-out(i,j);
                   out(i,j) = out(i,j) + x*(1-rand^((1-generace/G)^5) );
               else
                   x = out(i,j)-xMIN;
                   out(i,j) = out(i,j) + x*(1-rand^((1-generace/G)^5) );
               end
           end
       end
    end
    


   for i=1:length(out(:,1))
     for j=1:vstupu
       if (out(i,j)>xMAX) 
           out(i,j)=xMAX-0.2*(out(i,j)-xMAX);
       end
       if (out(i,j)<xMIN) 
           out(i,j)=xMIN+0.2*(xMIN-out(i,j));
       end
     end
   end

