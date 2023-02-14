#include "pilha.h"

Pilha* cria_pilha()
{
    Pilha *p = NULL;
    return p;
}

Pilha* push(Pilha *p, void* elemento)
{
   return(insere_inicio(p, elemento));
}

int eh_vazia_pilha(Pilha *p)
{
    if (p == NULL)
        return 1; //pilha esta vazia
    else
        return 0; //a pilha tem valores
}

//versao 1
void* pop(Pilha **p)
{
    Pilha *pont = *p;
    void* resposta = NULL;
    if (eh_vazia_pilha(*p) == 0)
        resposta = remove_inicio(&pont);// ou poderia ser remove_inicio(&(*p));
    return resposta;
}
/*
versao 2
Pilha* pop(Pilha *p, int *reposta)
{
    *resposta = -1;
    if (!eh_vazia_pilha(p))
        *resposta = remove_inicio(&p);
    return p;
}
*/



void* top(Pilha *p)
{
    if (!eh_vazia_pilha(p))
        return p->info;
    else
        return NULL;
}
