#include <stdio.h>

void toUpper(char *s){
    for(int k=0; s[k]; s++){
        if(s[k]>='a' && s[k] <='z'){
            s[k]-=32;
        }
    }
}

int main (){
    char s[]= "casa";
    toUpper(s);
    printf("%s", s);
return 0;}


/**

int srtlen(char *s){

    int n=0;
        while(s[n]){
            n++;
        }
        return n;
    }

int main (){
    printf("%d", strlen("casa caiu"));
return 0;}

//////////////////


int main (){

    int c=(int) 'a';
    printf("%d", c);
return 0;}

**/
