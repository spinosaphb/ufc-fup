//PALÍNDROMO
#include <stdio.h>
int main(){
int n, i, acc=0;
    for(i=0; i<=1000000; i++){
    int r=0, dig;
    n=i;
        while (n>0){
            dig = n%10;
            r = 10*r + dig;
            n/=10;
        }
        if(r==i) acc++;
    }
    printf("%d", acc); //quantidade palindromo
return 0;}
