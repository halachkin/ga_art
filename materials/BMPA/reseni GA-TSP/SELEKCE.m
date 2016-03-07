% SLEKCE(N/2,generace,fitness)
% IN:
%   typ - 1 ruleta; 2 pozicni selekce; 3 turnaj
%   N - kolik dvojic ma byt vygenerovano - aby byl pro krizeni zajisten sudy pocet rodicu
% OUT: novou generaci

function out=SELEKCE(Npul,gen,fit)



	% pozicni selekce
[fit index]=sort(fit);
suma=0;
        % vyroba rulety
for i=1:length(fit)  % tim zajisteno ze je to od nuly po max
  suma=suma+i;
end

        % hazeni kulickou
for i=1:(2*Npul)
  kulicka=rand*suma;
	% zjisti index kulicky v rulete
  j=0;
  suma2=0;
  while(kulicka>suma2),
    j=j+1;
    suma2=suma2+j;
  end
  	% prirad prezivsiho jedince
  out(i,:)=gen(index(j),:);
end
        
