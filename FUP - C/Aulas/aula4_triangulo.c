#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(){
int a,b,c,d=0,stop=0,ctotal=0;
    a=b=c=0;

    for(a=1; !stop; a++){
        for(b=1; b<a; b++){
            for(c=1; c<=b; c++){
                if((a*a) == (b*b) + (c*c)){
                d++;
                }else if((a+b+c)>300){
                stop=1;
                }
                if(a > abs(b-c) && a < (b+c)){ //[b-c] < a && a < [b+c])
                ctotal++;
                }
            }
        }
    }
    printf("%d %d", d, ctotal);
    printf("\n%.2e %%", d/(ctotal*100.0));
return 0;}
