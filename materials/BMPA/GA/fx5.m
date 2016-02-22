function out = fx5(in)

out=sin(log2(abs(in+0.1)))*log(in+1001)*(0.001*in+1);

if (abs(in)>1000) out=-Inf;end;