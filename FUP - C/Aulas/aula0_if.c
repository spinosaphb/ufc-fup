#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv){
	float x, y;

	x = sqrt(1.44);
	y = 2.4/2;

	if(fabs(x - y)<10.E-5){
		printf("Condição 1: Iguais -> ");
		printf("%f %f\n", x, y);
	}else{
		printf("Condição 1: Não iguais -> ");
		printf("%f\n%f\n", x, y);
	}

	if (x == y){
		printf("Condição 2: Iguais -> ");
		printf("%f %f", x, y);
	}else{
		printf("Condição 2: Não iguais -> ");
		printf("%f\n%f", x, y);
	}

	return 0;
}
