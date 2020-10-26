#include <stdio.h>
int main(){
    int x = 111;
    int i;
    int b = 1;


        for (i=2; i<x; i++)
            if(x % i == 0){
                b = 0;
                break;
            }
        if (b ==1 ){
            printf("Primo\n");
        } else{
            printf("Não primo\n");
        }

    return 0;
}
