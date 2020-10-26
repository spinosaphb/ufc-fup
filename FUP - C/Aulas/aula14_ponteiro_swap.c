#include <stdio.h>
int main(){
        int v[5]={1,2,5,4,7};
        int *p=&v[0]; // ou int *p=v;
            for(int i=0; i<5; i++){
                printf("%d", p[i]);
            }
return 0;}


/**

int main(){
int x = 7;
    int* p = &x;
    *p*=2;
    printf("%d", x);
return 0;


//PASSAGEM POR COPIA
#include <stdio.h>
void swap(int a, int b){
int c=a;
a=b;
b=c;}

int main(){
        int x=2;
        int y=3;
        swap(x, y);
        printf("%d %d", x, y);
return 0;}


//PASSAGEM TROCA
#include <stdio.h>
void swap(int *p, int *q){
int a=*p;
*p=*q;
*q=a;}

int main(){
        int x=2;
        int y=3;
        swap(&x, &y);
        printf("%d %d", x, y);
return 0;}

**/
