#include <stdio.h>
#include <stdlib.h>
// #include "arvoreb.h"
#include "arvorebplus.h"

int main()
{
    Node *raiz;

    raiz = NULL;

    raiz = inserir(raiz, 5, 33);
    raiz = inserir(raiz, 15, 21);
    raiz = inserir(raiz, 25, 31);
    raiz = inserir(raiz, 25, 41);
    raiz = inserir(raiz, 45, 10);

    printArvore(raiz);

    return 0;
}
