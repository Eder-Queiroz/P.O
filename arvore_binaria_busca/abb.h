#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
//#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//BST

struct no
{
        int info;
        struct no* esq;
        struct no* dir;
};

typedef struct no No;

/*
Cria��o
Destrui��o
Status (vazia)
Opera��es B�sicas
Inser��o
Consulta
Remo��o
*/

int abb_eh_vazia(No *raiz);
No* abb_insere(No* raiz, int info);
int abb_busca(No* raiz, int info);
No* abb_remove(No* raiz, int info);
No* abb_libera(No* raiz);
No* cria_no(int info);
No* abb_em_ordem(No* raiz);
void remocao_por_copia(No* q,int info);


#endif // ABB_H_INCLUDED
