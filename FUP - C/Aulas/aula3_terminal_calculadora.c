#include <stdio.h>
int main (){
char op;
int x, y;
int b=1;

    //do{
    for(;b;){
        printf("$ ");
        scanf("%c %d %d", &op, &x, &y);
        //printf("%c %d %d", op, x, y);

            switch(op){
            case '+':
                printf("%d", x+y);
                break;
            case '-':
                printf("%d", x-y);
                break;
            case '*':
                printf("%d", x*y);
                break;
            case '/':
                printf("%d", x/y);
                break;
            case 'e':
                printf("Até logo!");
                b=0;
                break;
            default:
                printf("Operação inválida!");
                break;
            }
        }
    //}while(b);

return 0;}
