//multiplicação estilo ensino fundamental

#include <stdio.h>
#include <math.h>

int main(){
    int k, acc = 0;
    int x = 1234;
    int u[4], v[10];
    int j=9;

        for(k=3; k>=0; k--){
            u[k] =  x%10;
            x/=10;
        }

        for(k=0; k<10; k++){
            v[k] = 0;
        }

            for(k=3; k>=0; k--){
                int m = 12*u[k] + acc;
                v[k] = m%10;
                acc = m/10;
            }


        for(k=0; k<4; k++){
        printf("%d", v[k]);
        }

        k=3;
        while(k>=0){
            int m = u[k]*12 + acc;
            v[j] = m%10;
            acc = m/10;
            k--, j--;
        }
            if(acc > 0){
                v[j] = acc;
            }




return 0;}
