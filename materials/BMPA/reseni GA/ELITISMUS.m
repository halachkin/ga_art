% vybere zadany pocet nejlepsich jedincu z generace

function out=ELITISMUS(rad,gen,fit)

rad=round(rad);
if (rad<0) rad=0;end
if (rad>5) rad=5;end

if (rad>0)
    [ser index]=sort(fit);
    for i=1:rad
        out(i,:)=gen(index(length(fit)+1-i),:);
    end
else
    out=[];
end
