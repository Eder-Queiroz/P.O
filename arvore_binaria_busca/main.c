#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

int main()
{
    No* raiz = NULL;

    raiz = abb_insere(raiz, 10);
    raiz = abb_insere(raiz, 3);
    raiz = abb_insere(raiz, 12);
    raiz = abb_insere(raiz, 9);
    raiz = abb_insere(raiz, 9);
    abb_remove(raiz, 12);

    abb_em_ordem(raiz);

    return 0;
}
