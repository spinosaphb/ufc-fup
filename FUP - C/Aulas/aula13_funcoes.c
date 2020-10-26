#include <stdio.h>
//O C chama a função em sequencia, ou seja a próxima
//Prototipação é declarar a função
//para o programa reconhecer a função em qualquer lugar

void A();
void B();

void A(){
    printf("Sou A\n");
    B();
}
void B(){
    printf("Sou B\n");
    A();
}
int main(){
    A();
    B();
}

/**

//Numero primo 1 para primo, 0 para não primo, -1 para negativo(inválido)
int primo(int n){
    if(n<2){
        return 0;
    }

    int b=2;

    while(b*b <= n){ //while 2*2(4) <= n
        if(n%b==0){ //se resto da div for = 0 então não primo
            return 0; //
        }
        b++;
    }return 1;
}

int main(){
    int v[100], n, i=0;

    while (i<100){
        if(primo(n)){
            v[i] = n;
            i++; n++;
        } else{
            n++;
        }
    }

    for(i=0; i<100; i++){
        printf("%d %d\n", i, v[i]);
    }

return 0;}

**/


/**

int main(){
    printf("%d", fnc);
return 0;}

int fnc(int a, int b){
    int c = a+b;
return c;}

**/
