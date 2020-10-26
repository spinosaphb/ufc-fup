//equacao 2 grau
#include <stdio.h>
#include <math.h>
#define false 0;
#define true 1;
typedef int bool;

bool eq2g(float a, float b, float c, float *px1, float *px2){
    if(fabs(a)<1.0E-8) //quantas casa conside pro valor ser 0
        return false;

    float d = (b*b)-(4*a*c);
        if(d<0){
            return false;
        }
            *px1 = ((-b+sqrt(d))/(2*a));
            *px2 = ((-b-sqrt(d))/(2*a));
            return true;
}

int main(){
//float x[] =[-2, 4, -1]; se na func existir um vetor pra recebet
    for(;;){
    float a=0, b=0, c=0, px1, px2;
    printf("Coeficientes\n");
        scanf("%f%f%f", &a, &b, &c);
        if(eq2g(a, b, c, &px1, &px2))
            printf("%f %f\n", px1, px2);
        else
            printf("Erro!\n");
    }
return 0;}


/**

//função sem return mas aponta pro endereço dos valores
#include <stdio.h>
void minmax(int u[], int n, int *a, int *b){
    *a = u[0];
    *b = u[0];

        for(int i=1; i<n; i++){
            if(u[i]<*a)*a=u[i];
            if(u[i]>*b)*b=u[i];
        }
}

int main(){
int x[] = {1, 2, 3 ,4 ,5, 6};
int max, min;
minmax(x, 6, &min, &max);
printf("%d%d", min, max);
return 0;}

**/
