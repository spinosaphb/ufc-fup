#include <stdio.h>
int main(){
int a, b, c, i;

a=b=1;
printf("%d\n%d\n", a, b);

for (i=3; i<=50; i++) {
c=a+b;
printf("%d \n", c);
a=b;
b=c;
}
return 0;
}
