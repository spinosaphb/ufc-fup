#include <stdio.h>
int main(){
    int x=2;
    int i = 2;
    int b = 1;
        while((i*i) <= x){
            if(x % i == 0){
                b = 0;
                break;}
                i++;
            }


        if (b ==1 ){
            printf("Primo\n");
        } else{
            printf("Não primo\n");
        }
return 0;}
