#include <stdio.h>
#include <math.h>
#define poly(x) ((x)*(x)*(x))-6*((x)*(x))+11*(x)-6
#define ABS(x) (x)>0? (x):(-(x))
//x^6+11x-6
int main(){
     float a = 0.0,b = 5.0, c;
     int bool=1;
        do{
        c = (a+b)/2.0;
            if(poly(a) * poly(c) < 0){
            b=c;
            }else if(poly(b) * poly(c) < 0){
            a=c;rand
            }else{
            bool=0;
            printf("Não pode calcular\n");
            break;
            }
        }while(ABS(poly(c)) > 1.0E-5);
        printf("%f\n", c);
return 0;}
