% SLEKCE(N,generace,fitness)
% IN:
%   typ - 1 ruleta; 2 pozicni selekce; 3 turnaj - jeden naprogramuj
%   N - kolik potomku ma byt vygenerovano
% OUT: nova generace
% pozicni selekce

function out=SELEKCE(N,gen,fit)

% [gen i] = unique(gen,'rows');
% fit = fit(i) ;
%delete duplicates gen  with a tolerance
tol = 0.0001; % tolerance
[~, ii] = sortrows(gen);
ii_unique = ii(logical([1; any(diff(gen(ii,:))>tol,2)]));
fit = fit(logical([1; any(diff(gen(ii,:))>tol,2)]));
gen = gen(sort(ii_unique),:); % result

fit = fit(isfinite(fit));
fit = transpose(fit);
[rulette ind] = sort(fit);
rulette = fliplr(rulette);
ind = fliplr(ind);
for m = 1:N
    range(1) = 0;
    for i = 2:length(ind) + 1
        range(i) = ind(i-1);
        range(i) = range(i-1) + range(i); 
    end
    roll = rand*max(range);
    if(length(ind) == 0)
        continue;
    end
    for j = 1:length(range) - 1
        if(roll >= range(j) & roll<=range(j+1))
            roll = ind(j);
            break;
        end
    end
    if(roll==0)
        continue;
    end
    out(m,1:size(gen,2)) = gen(ind(roll),1:end);
    gen(ind(roll),:) = [];
    ind(ind>ind(roll)) = ind(ind>ind(roll)) - 1;
    ind(roll) = [];
    range = [];
end

        
