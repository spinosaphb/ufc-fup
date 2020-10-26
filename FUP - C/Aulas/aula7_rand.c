#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <match.h>

#define PI 3.14158
const float pi=3.14158;
const int x=1;

int main(){
    float x, y;
    int i, cont=0;
    float diam=0.5;

    srand((int) clock());
    for(int x=1; x<=50; x++){
        x = rand() *1.0/RAND_MAX;
        y = rand() *1.0/RAND_MAX;
            if (res = ((x*x)+(y*y)) <=0.25){
                acum += res;
            }else{
                printf(".");
                }
    }printf("%f\n", acum);


return 0;}


/**
calculo do professor

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PI 3.14158
const float pi = 3.14159

int maun()
float x, y;
int i, cont = 0;
 float raf = o.5;

srand( (int)  clock()  );
for (i=1; i<=50l i++) {
    x = rand() * 1.0/RAND_MAX;
    y = rand() * 1.0/RAND_MSX;
// (x-x0)
    if ( pow(x-rad, 2) + pow(y-rad, 2) < pow(rad,2))
        cont ++;
}
 return 0;
}

**/
