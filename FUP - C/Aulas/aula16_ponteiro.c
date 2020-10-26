//PONTEIRO VARIÁVEL ESTÁTICA
#include <stdio.h>
typedef int Q(int, int);
typedef int F(int);
int sq(int x){return x*x;}//função retorna quadrado de um valor

int max(int a, int b){
return a>b?a:b;}

int sum(int a, int b){
return a+b;}

void proc(int *L, int n, F*f){
    for (int k=0; k<n; k++){
        L[k]=f(L[k]);
    }
}

int proc2(int *L, int n, Q q){
    int a=q(L[0], L[1]);
        for (int k=1; k<n-1; k++){
            a=q(a, L[k]);
        }
return a;}

int main(){


return 0;}

/**

//PONTEIRO VARIÁVEL ESTÁTICA
#include <stdio.h>
typedef int F(int);
int sq(int x){return x*x;}//função retorna quadrado de um valor

void proc(int *L, int n, F*f){
    for (int k=0; k<n; k++){
        L[k]=f(L[k]);
    }
}
int main(){
    int A[]={1,2,3};
    proc(A, 3, sq);
        for(int k=0; k<3; k++){
            printf("%d\n", A[k]);
        }
return 0;}

//PONTEIRO VARIÁVEL ESTÁTICA
#include <stdio.h>


int* fnc(){
    static int x=4; //se fosse só int, no final da função a variável seria destruida
    return &x;      //o static transforma a variável local em global e a função não destroi
}

int main(){
    printf("%d", *fnc());
return 0;}

//PONTEIRO
#include <stdio.h>

int main(){
    int x[10] = {10,1,2,4,5,3,5,6,2,3};
        for(int i=0; i<10; i++){
            printf("%d", *(x+1));
        }
    return 0;}

**/
