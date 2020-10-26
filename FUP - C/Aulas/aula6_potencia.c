//BASE E EXPOENTE
#include <stdio.h>
int main(){
    float a=8.0, p=1.0; //a=base
    int n = 2, i; //n=expoente

    for(i=1; i<=n; i++)
        p *= a;
        printf("%f", p);

return 0;}
