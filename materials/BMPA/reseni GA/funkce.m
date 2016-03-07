function out = funkce(in)

if length(in)==6
out = fx1(in(1))+fx2(in(2))+fx2(in(2))*fx3(in(3))/4+fx4(in(4))-...
      fx5(in(5))+fx6(in(6))+log2(abs(fx5(in(5))*fx6(in(6)))+0.1)+...
      fx1(in(4))*fx3(in(6))*fx5(in(2))/80+...
      fx2(in(5))*fx4(in(1))*fx6(in(3))/90;
else
out=-Inf
end