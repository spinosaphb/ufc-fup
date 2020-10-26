//descobrir qtdd digit fatorial de 1000 apartir da formula (1 + piso de log de 1000)
// soma dos valores do logaritmo
#include <stdio.h>
#include<math.h>
int main(){
    double d = 0.0;
    int k, m;
    int x;
    scanf("%d", &x);

    for (k=1; k<=x; k++){
        d+= log2(k); //logs de 1 a 1000
    }

    int len = 1+(int) floor(d); //soma de todos os logs de 1 a 1000
    int fat[len +1];

        for (k=0; k<len+1; k++){
            fat[k] = 0;
            fat [len] = 1;
        }

        for(k=1; k<=x; k++){
            double acc=0;
            int j = len;

            do{
            for(int j = len; j>=0; j--){}//trocar do while por for
                m = k * fat[j] + acc;
                fat[j] = m%10;
                acc = m/10;
                j--;
            } while(m>=0);

            if (acc>0){
                fat[j] = acc;
            }
        }

        for(int i = 1; i<len+1; i++){
            printf("%d", fat[i]);
        }


return 0;}
