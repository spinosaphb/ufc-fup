#include <stdio.h>
int main(){
    int x = 2;
    int b;
    int count;

        for (;;){
        int i = 2;
        b=1;

            while((i*i) <= x){

                if(x % i == 0){
                    b = 0;
                    //count++;
                    break;
                }

            i++;
            }

            if (count == 20){
            break;
            }

        printf("%d \n", x);
        x++;
        }

return 0;}

