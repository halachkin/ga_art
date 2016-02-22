% vybere zadany pocet nejlepsich jedincu z generace
% minimalne 0, maximalne 5

function out=ELITISMUS(rad,gen,fit)

gen = gen(~isnan(fit),1:end);
fit = fit(~isnan(fit));
gen = gen(isfinite(fit),1:end);
fit = fit(isfinite(fit));
if (rad<=0 | rad>5)
    out = [];
    return;
else
    fit = transpose(fit);
    gen(1:end,size(gen,2) + 1) = fit;
    [t a b] =  unique(gen(1:end,1:end-1),'rows');
    gen  = gen(a,:);
    [X ix] = sort(gen(:,end));
    gent = flip(gen(ix,:));
    gen = gent(:,1:end-1);
    for i = 1:rad
        out(i,1:size(gen,2)) = gen(i,1:end);
    end
end
