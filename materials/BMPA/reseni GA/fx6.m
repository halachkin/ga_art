function out = fx6(in)

out=-sin(in/100)*exp(-in/400);

if (abs(in)>1000) out=-Inf;end;