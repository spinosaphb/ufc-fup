#include <stdio.h>
#include <stdlib.h>
int **matCreate(int n){
    int **p=(int **) malloc(n * sizeof(int *));
        for(int j=0; j<n; j++){
            p[j] = (int*) malloc(n*sizeof(int));
        }
        return p;
}
void matDestroy(int **p, int n){
    for(int j=0; j<n; j++){
        free(p[j]);
    }
    free(p);
}
void matPrint(int **p, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%d\t", p[i][j]);
        }
        printf("\n");
    }
}

int **matSum(int **a, int **b, int n){
    int **c=matCreate(n);
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                c[i][j] = a[i][j]+b[i][j];
            }
        }
return c;}


int main(){
    int **x, **y, **z;
    x=matCreate(2);
    y=matCreate(2);
    x[0][0]=1;
    x[0][1]=2;
    x[1][0]=3;
    x[1][1]=4;

    y[0][0]=5;
    y[0][1]=6;
    y[1][0]=7;
    y[1][1]=8;

    z=matSum(x, y, 2);
    matPrint(z, 2);
    matDestroy(x, 2);
    matDestroy(y, 2);

return 0;}
