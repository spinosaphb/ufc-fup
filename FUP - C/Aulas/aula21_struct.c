#include <stdio.h>
#include <string.h>
//para acessar uma struct deve-se ultilizar o ponto(.)
/*typedef struct _pessoa_{
  int idade;
  char nome[50];
  float salario;
}pessoa;
pessoa x;
x.idade = 40;
x.salario = 400000;
strcpy(x.nome,"casa");*/
typedef struct{
  int x;
  int y;
  float pi;
}circle;

int main(){
circle c = {1,2,37};//definindo os dados de c com base na struct circle
circle *p;
p = &c;
(*p).x;//ou p->x
(*p).y;//ou p->y
(*p).pi;//ou p->pi
}
