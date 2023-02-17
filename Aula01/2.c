#include <stdio.h>
#include <stdlib.h>

/*B. arvore*/

struct no
{
        int info;
        struct no* esq;
        struct no* dir;
};

typedef struct no No;

No* cria_no(int info)
{
    No* novo = (No*) malloc(sizeof(No));
    novo->esq = novo->dir = NULL;
    novo->info  = info;
    return novo;
}

int abb_eh_vazia(No *raiz)
{
    if (raiz == NULL)
        return 1;
    else
        return 0;
}

No* abb_insere(No* raiz, int info)
{
    No* q = raiz;
    No* p = NULL; //pai do q
    int flag = 0;

    while(q != NULL && flag != 1)
    {
        p = q;
        if(q->info < info)
            q = q->dir;
        else if(q->info > info)
            q = q->esq;
        else
            //igual
            flag = 1;
    }
    if (!flag) // flag == false
    {
        if (raiz != NULL)
        {
            if (p->info < info)
                p->dir = cria_no(info);
            else
                p->esq = cria_no(info);
        }
        else
            raiz = cria_no(info);
    }

    return raiz;
}


int abb_busca(No* raiz, int info)
{
    No* aux = raiz;

    while(aux != NULL && aux->info != info)
    {
        if(aux->info < info)
            aux = aux->dir;
        else
            aux = aux->esq;
    }
    if ( aux == NULL)
        return 0;
    else
        return 1;
}

No* abb_em_ordem(No* raiz)
{
    if(raiz != NULL)
    {
        abb_em_ordem(raiz->esq);
        printf("%i ", raiz->info);
        abb_em_ordem(raiz->dir);
    }
}

No* abb_libera(No* raiz){
  if(raiz != NULL)
    {
        abb_libera(raiz->esq);
        abb_libera(raiz->dir);
        free(raiz);
    }

}

/*Fim B. arvore*/

int main() {



    return 0;

}
