#include <stdio.h>
#include <stdlib.h>
int main(){
    int x[3][2] = {{1,2},{4,1},{8,5}};

    for(int i=0; i<3; i++){
        for(int j=0; j<2; j++){
            printf("%d", x[j][i]);
        }
        printf("\n");
    }
return 0;}
