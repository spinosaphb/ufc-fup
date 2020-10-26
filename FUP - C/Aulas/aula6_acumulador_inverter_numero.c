//INVERTER NÚMERO
#include <stdio.h>
int main(){
int n=15324, r=0; //n=número r=reverso
while (n>0){
r=10*r+(n%10);
n/=10;
printf("%d\n", n);
}
//printf("%d", r); //mostra numero reverso
return 0;}

/**outra forma
while (n>0){
dig = n%10;
r = 10*r + dig;
n/=10;
}
printf("%d", r);
**/
