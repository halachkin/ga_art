function out = fx1(in)

if (in<-500)
out=1/(-in)*5000*sin(in/50);
elseif (in<500)
out=(-in)/100*sin(in/50)+2.5;    
else
out=1/in*500+3;
end


if (abs(in)>1000) out=-Inf;end;