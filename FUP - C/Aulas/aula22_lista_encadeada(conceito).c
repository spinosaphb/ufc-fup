#include <stdio.h>
#include <malloc.h>
#include "aula22_lista_encadeada(conceito).h"

List create(){
    List list;
    list.root = NULL;
    list.len = 0;
    return list;
}

Node *nodeCreate(int x){
    size_t tam = sizeof(Node);
    Node *node = (Node *)malloc(tam);
    node -> data = x;
    node -> next = NULL;
    return node;
}

void addBegin(List *list, int x){
    Node *node = nodeCreate(x);
    node -> next = list -> root;
    list -> root = node;
    list -> len++;
}

void addEnd(List *list, int x){
    Node *node = nodeCreate(x);
    Node *p = list -> root;
    while(p -> next != NULL){
        p = p -> next;
    }
    p -> next = node;
}

void delete(List *list, int x){
    if(list -> root == NULL)
        return;
    Node * anterior = list -> root;
    Node * atual = list -> root;
    while (atual != NULL){
        if (atual -> data == x){
            anterior -> next = atual -> next;
            list -> len --;
            return;
        }
        anterior = atual;
        atual = atual -> next;
    }
}

void _destroy(Node *node){
    if(node == NULL){
        return;
    }
    _destroy(node -> next);
    free(node);
}

void destroy(List *list){
    _destroy(list -> root);
}

void _reverse(Node *node){
    if(node == NULL){
        return;
    }
    _reverse(node -> next);
    /**node = **/ 
}

void reverse(List *list){

}

void print(List *list){
    Node *p = list -> root;
    while(p != NULL){
        printf("%d ", p -> data);
        p = p -> next;
    }
}

int main(){
    List lista = create();
    addBegin(&lista, 2);
    addBegin(&lista, 5);
    addBegin(&lista, 7);
    addEnd(&lista, 9);
    printf("Tamanho da lista: %d \n", lista.len);
    print(&lista);
    delete(&lista, 5);

    printf("\nDeletando o 5\n");
    print(&lista);
    printf("\nTamanho da lista: %d \n", lista.len);

    destroy(&lista);
    print(&lista);
    return 0;
}