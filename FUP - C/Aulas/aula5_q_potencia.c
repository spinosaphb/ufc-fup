#include <stdio.h>
#include <math.h>
int main (){
int a,b, c=1, i;
int p;
printf("Cálculo de potência (inteiro):\n");
scanf("%d %d", &a, &b);

for(i=0; i<b; i++){
c*=a; //1*a
} printf("%d", c);

/**usando função pow
p = pow(a,b);
printf("%d", p);
**/
return 0;}
