#include <stdio.h>
#include <math.h>
int main (){
int qtd, soma, num;
    qtd=soma=0;

    do{
        scanf("%d", &num);
            if(num>0){
                qtd++;
                soma += num;
            }
    }while(num>=0);
        printf("Quantidade: %d \nSoma: %dMédia: %.2f", qtd, soma, (soma/(qtd*1.0)));
return 0;}
