#include "listasimples.h"
#include "listasimples.h"



No* cria_no(void* valor)
{
    No* novo;
    novo = (No*) malloc(sizeof(No));

//inicializar campos
    novo->prox = NULL;
    novo->info = valor;

    return novo;
}


No* insere_inicio(No *L, void* valor)
{
    No* nuevo = cria_no(valor);
    if (L != NULL)
    {
        nuevo->prox = L;
    }
    return nuevo;
}






No* libera_lista(No *L)
{
    No *aux = L;

    while (aux != NULL)
    {
        L = L->prox;
        free(aux);
        aux = L;
    }
    return NULL;
}

No* insere_fim(No* L, void* valor)
{
    No* novo = cria_no(valor);
    No* aux = L;

    if (L == NULL)
    {
        L = novo;
    }
    else
    {
        //  for (aux = L; aux->prox != NULL; aux = aux->prox)

        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
    return L;
}


void* remove_inicio(No** L)
{
    No* aux = *L;
    void* pont;

    if (*L != NULL)
    {
        *L = aux->prox;
    }
    pont = aux->info;
    free(aux);
    return pont;
}
