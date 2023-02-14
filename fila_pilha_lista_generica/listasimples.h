#ifndef LISTASIMPLES_H_INCLUDED
#define LISTASIMPLES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>


struct no
{
    void *info;
    struct no *prox;
};

typedef struct no No;


No* cria_no(void*);

No* insere_inicio(No*, void*);

No* libera_lista(No *L);


No* insere_fim(No* L, void* valor);

void* remove_inicio(No** L);


#endif // LISTASIMPLES_H_INCLUDED
