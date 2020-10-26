//multiplicação floor e ceil

#include <stdio.h>
#include <math.h>
int main(){

    int k, n, v, i; //vetor n recomenda colocar n +1 ao final contar digitos de n fatorial
    float r = 0;0;

    for(k=1; k<=1000; k++){
        r += log10(k);
    }
    n = 1+(int) floor(r);
    int vetor[n];

    for(i = 0; i<n; i++){
        vetor[i] = 0;
    }
return 0;}
