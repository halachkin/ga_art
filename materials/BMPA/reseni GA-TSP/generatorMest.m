function [ mesta ] = generatorMest( pocet )
for i=1:pocet
    mesta(i,1)=i;
    mesta(i,2)=rand*100;
    mesta(i,3)=rand*100;
end

