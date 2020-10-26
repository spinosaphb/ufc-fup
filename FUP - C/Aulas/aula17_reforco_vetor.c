//quantidade de elementos
#include <stdio.h>

int contem(int vet[], int n, int indice){
    for(int i=0; i < indice; i++)
        if(vet[i] == vet[indice]){
        return 1;
    }
    return 0;
}

int main(){
    int tam, qtd = 0;
    scanf("%d", &tam);
    int animais[tam];

    for(int i=0; i<tam; i++){ //inicializando o vetor
        scanf("%d", &animais[i]);
    }
        for(int i=0; i<tam; i++){ //percorrer vetor
            if(!contem(animais, animais[i], i)){
                qtd++;
            }
        }
    printf("%d\n", qtd);
return 0;}




/**
//fup is fun cabeças vão rolar
#include <stdio.h>
//    remover(vetor, 4, &numJog);
//    numJog--;
//
//    for(int i=0; i<numJog; i++){
//        printf("%d", vetor[i]);
//        printf(" :: %d", numJog);
//    }


void remover(int vetor[], int n, int tam){
    for(int i=n; i<tam-1; i++){
        vetor[i] = vetor[i+1];
    }
}


int main(){
    int numJog, inicial;
    scanf("%d %d", &numJog, &inicial);

    int vetor[numJog];

    for(int i=0; i<numJog; i++){ //preencher vetor
        vetor[i] = i+1;
    }
    int atual = inicial-1;
    while(numJog > 1){
        for(int i=0; i<numJog; i++){
            printf("%d :: ", vetor[i]);
            printf("-> %d \n", atual);
            remover(vetor, (atual+1) % numJog, numJog);
            atual = (atual+1 % numJog);
            numJog--;
        }
    }
    printf("%d", vetor[0]);


return 0;}



//quantidade de elementos
#include <stdio.h>

int contem(int vet[], int n, int indice){
    for(int i=0; i < indice; i++)
        if(vet[i] == vet[indice]){
        return 1;
    }
    return 0;
}


int main(){
    int tam, qtd = 0;
    scanf("%d", &tam);
    int animais[tam];

    for(int i=0; i<tam; i++){ //inicializando o vetor
        scanf("%d", &animais[i]);
    }
        for(int i=0; i<tam; i++){ //percorrer vetor
            if(!contem(animais, animais[i], i)){
                qtd++;
            }
        }
    printf("%d\n", qtd);
return 0;}

**/
