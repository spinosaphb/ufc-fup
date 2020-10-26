#include <stdio.h>
#include <stdlib.h>


int main(){
    float vetor[1000];
    //for(int i=0;i<1000;i++)
        //vetor[i] = i*i;
    //FILE *file = fopen("file.bin","wb");
    FILE *file = fopen("file.bin","rb");
    for(int i=0;i<1000;i++)
        fread(vetor+i,1,sizeof(float),file);
        




    fclose(file);
    
    for(int i=0;i<1000;i++)
        printf("%f\n",vetor[i]);
    
    return 0;
}