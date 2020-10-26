#include <stdio.h>
#include <malloc.h>

typedef struct __Node__{
    int data;
    struct __Node__ *next;
} Node;

typedef struct {
    Node *root;
    int len;
} List;