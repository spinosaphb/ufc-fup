#include <stdio.h>

int main(){
    int r1,r2,r3;
    char c1,c2,c3;
    scanf("%d%d%d",&r1,&r2,&r3);
    if(r1>r2){
        if(r1>r3)
            c1 = 'G';
        else{
            if(r3>r2){
                printf("M P G");
                return 0;            
            }else
                
        }       
    }else if(r2 > r3){
        if(r2>r1)
            c2 = 'G';
        else
            if(r1>r3){
                printf("G M P");
            }
    }


}