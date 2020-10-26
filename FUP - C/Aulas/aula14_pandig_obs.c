#include <stdio.h>
#include <time.h>

#define MAX_NUM 9876543210

typedef unsigned long int Int;

int isPanDig(Int x) {
    static int  d[10];
    int n = 0;

    if (x > MAX_NUM) return 0;

    while (x > 0) {
        d[n] = x % 10;
        x/=10;
        n++;
    }
    for (int i = 0; i<n-1; i++)
        for (int j = i+1; j<n; j++)
            if (d[i]==d[j])
               return 0;
    return 1;
}

int isPrimo(Int x) {
    for (int d = 2; d*d <= x; d ++)
        if (x % d != 0)
            return 0;
    return 1;
}

void printTimeLabeled(Int secs) {
    Int a = secs;
    Int h = a/3600;
    a = a - h * 3600;
    Int m = a/60;
    a = a - m * 60;
    if (h>99) h = 99;
    printf(" [%02ldh-%02ldm-%02lds] ",
      h, m, a);
}

void clearLine() {
    for (int i=0;i < 100; i++)
        printf("\b");
}

int main() {
    Int cont = 0;
    clock_t c0 = clock();
    for (Int k = 1; k<MAX_NUM; k++) {
        clearLine();
        if (isPrimo(k)  && isPanDig(k))
            cont++;
        float p = (k-1)*1.0/(MAX_NUM-1);
        clock_t cf = clock();
        Int secs = (cf - c0)/CLOCKS_PER_SEC;
        Int r = (Int) ( secs*(1-p)/p );
        printf("%5.1f%%\t\t", p*100.0);
        printTimeLabeled(r);
    }
    printf("\n\nTotal: %ld\n", cont);
    return 0;
}







/**

função
modualrização
vetor
string

HEXAGONO DAS VARIAVEIS
1NOME
2TIPO
3VALOR
4ENDEREÇO
5ESCOPO
6TEMPO DE VIDA

//função estática
#include <stdio.h>
#include <math.h>
void fnc(){
    static int x=0;
        x++;
        printf("%d", x);
}

int main(){
    for(int k=0; k<16; k++){
        fnc();
    }

return 0;}


**/
