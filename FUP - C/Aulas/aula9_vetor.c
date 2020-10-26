//VETOR 2
#include <stdio.h>
int main(){
    int n, len=0, x;
        scanf("%d", &n);
            x=n;
            while(x!=1){
                if(x%2==0){
                    x/=2;
                } else{
                    x=3*x+1;

                }len++;

            }//printf("Comprimento %d\n", len);

            int seq[n];

                for(int i=0; i<len; i++){
                    x=n%2==0 ? n/2 : 3*n+1;
                    seq[i]=x;
                    n=x;
                    printf("%d\n", n);
                }

return 0;}



/**

//VETOR
#include <stdio.h>
int main(){
int n, i;
    scanf("%d", &n);
    int x[n];

        for(i=0; i<n; i++){
            x[i] = 3*i+1;
        }

        for(i=n-1; i>=0; i--){
            printf("%d, ", x[i]);
        }


return 0;}

**/
