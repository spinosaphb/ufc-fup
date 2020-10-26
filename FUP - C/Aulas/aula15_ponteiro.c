// ALGORITMO DE ORDENAÇÃO SELECTION SORT
#include <stdio.h>

void sort (int *x, int n){
    for(int d = n-1; d>0; d--){
            for(int i=0; i<d; i++){
                if(x[i]>x[d]){
                    int m=x[d];  //mesmo que swap
                    x[d]=x[i];   // swap(&x[i], &x[k]
                    x[i]=m;      // swap (x+i, x+k)
                }
            }                    // x[k] <=> *(x+k)
    }                        // &x[k] <=> x+k
}





int main(){
    int w[]={5,3,2,6,1};
    sort(w, 5);
        for(int k=0; k<5; k++){

            printf("%d", w[k]);
        }
return 0;}

/**
int main (){
    int srtlen(char *s){
        int n=0;
        while(s[n] != '\0'){
            n++;
        }
    }
return 0;}

**/
