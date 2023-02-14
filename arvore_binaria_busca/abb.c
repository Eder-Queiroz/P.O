#include "abb.h"

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
        printf("%d ", raiz->info);
        abb_em_ordem(raiz->dir);
    }
}

No* abb_remove(No* raiz, int info)
{

    No* q = raiz;
    No* p = NULL; //pai do q
    No* f = NULL;

    while(q != NULL && q->info != info)
    {
        p = q;
        if(q->info < info)
            q = q->dir;
        else
            q = q->esq;
    }
    if (q != NULL)//encontrou o valor a ser removido
    {
        if (q->esq == NULL && q->dir == NULL)
        {
            if (raiz == q)
            {
                free(raiz);
                raiz = NULL;
            }
            else
            {
                if (p->esq->info == info)
                    p->esq = NULL;
                else
                    p->dir = NULL;

                free(q);
            }

        }
        else //so tem um filho na direita
        {

            if (q->esq == NULL)
                f= q->dir;
            else if (q->dir == NULL )
                f = q->esq;
            else //tem dois filhos
            {
                remocao_por_copia(q,info);
            }
            if(q == raiz)
            {

                raiz = f;
                free(q);
            }
            else
            {
                if (p->esq->info == info)
                    p->esq = f;
                else
                    p->dir = f;
                free(q);
            }
        }

    }
return raiz;
}

void remocao_por_copia(No* q,int info)
{

    //por sucessor
    No* s = q->dir;
    No* p = q;
    while (s->esq != NULL)
    {
        p = s;
        s = s->esq;
    }


    //troca
    q->info = s->info;
    p->esq = s->dir;
    free(s);

}

No* abb_libera(No* raiz){
  if(raiz != NULL)
    {
        abb_libera(raiz->esq);
        abb_libera(raiz->dir);
        free(raiz);
    }

}
