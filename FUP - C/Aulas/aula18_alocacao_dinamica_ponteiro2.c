#include <stdio.h>
#include <stdlib.h>
int *function(int n){
//static int u[n]; criar uma global sem saber valor (erro)

    int *u=(int *)malloc(n*sizeof(int)); //declar var recebendo o tam de n; malloc retorn ender de qlqr coisa; é como void *
        for(int i=1; i<=n; i++)
            u[i]=2*i+1;
return u;}


int main(){
    int *x = function(10);
        for(int i=1; i<10; i++){
            printf("%d", x[i]);
        }
        free(x);
return 0;}
