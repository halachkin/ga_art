function out = fx3(in)

if (in<-100)
out=log(1/(-in)*500*(sin(in/40)+1)^2+3)*2;
elseif (in<900)
out=((-in)/100*sin(in/50)+2.5);    
else
out=log(in*in)/3+3;
end


if (abs(in)>1000) out=-Inf;end;