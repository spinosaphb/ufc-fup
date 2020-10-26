#include <stdio.h>
#include <stdlib.h>
//cada campo da union usam a mesma memoria
typedef union{
    int x;
    char mask[4];
}crip;
int main(){
    int vet[10] = {0,1,2,3,4,5,6,7,8,9};
    char key = 123;
    for(int i=0;i<10;i++){
        crip w;
        w.x = vet[i];
        for(int y=0;y<4;y++){
            w.mask[y] = w.mask[y]^key;
        }
        vet[i] = w.x;
    }
    for(int i=0;i<10;i++)
        printf("%d\n",vet[i]);





    //00000101;
    //00001000;
    
    //00010000;
    //00001100;
    
    //printf("%ld\n",sizeof(char));
}
