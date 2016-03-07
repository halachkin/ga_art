function out = fx2(in)

if (in<-300)
out=1/(-in)*500*(sin(in/40)+1)^2;
elseif (in<600)
out=2*((-in)/100*sin(in/50)+2.5);    
else
out=1/in*500+3;
end


if (abs(in)>1000) out=-Inf;end;