#include <stdio.h>
int main(){

int i;
unsigned long long int mult=1;
for (i=1; i<=50; i++) /*if(i%2==0)*/{

mult *= i;
//printf("%d \n", i);
printf("%llu \n", mult);

}
return 0;
}
