function out = fx4(in)

if (in<-600)
out=0.01*in+10;
elseif (in<-400)
out=-0.0125*in*((in+600)/200) +(0.01*in+10)*((-in-400)/200);
elseif (in<-10)
out=-0.0125*in;
elseif (in<30)
out=1.06^in;
elseif (in<250)
out=log(in)*sin(in/50);
else
out=sin(log(in*in*in*2))*log(in)+2;
end

if (abs(in)>1000) out=-Inf;end;