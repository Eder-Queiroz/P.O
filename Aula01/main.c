/*Crie uma função iterativa que coloca os nós da ABB em uma lista duplamente encadeada em ordem*/

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

/*B. listaDupla*/

struct nod
{
    int info;
    struct nod *ant;
    struct nod *prox;
};
typedef struct nod Nod;

struct listad
{
        Nod *ini;
        Nod *fim;
};
typedef struct listad Listad;

Listad* cria_listad()
{
    Listad* novalista;
    novalista = (Listad *)malloc(sizeof(Listad));
    novalista->ini = novalista->fim = NULL;
    return novalista;
}

Nod* cria_nod(int valor)
{
    Nod* novo = (Nod*)malloc(sizeof(Nod));
    novo->ant = novo->prox = NULL;
    novo->info = valor;
    return novo;
}


Listad* insere_inicio_listad(Listad *L, int valor)
{
    Nod *novo= cria_nod(valor);

    if (L == NULL)
    {
        L = cria_listad();
        L->ini = L->fim = novo;

    }
    else
    {
        if (L->ini == NULL)
            L->ini = L->fim = novo;
        else
        {
            novo->prox = L->ini;
            L->ini->ant = novo;
            L->ini = novo;
        }
    }
    return L;

}



void mostra_listad(Listad* L)
{
    Nod* aux = L->ini;

    while(aux != NULL)
    {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n ");
}

Listad* insere_fim_listad(Listad* L, int valor)
{
    Nod *novo = cria_nod(valor);

    if (L == NULL)
    {
        L = cria_listad();
        L->ini = L->fim = novo;
    }
    else
    {


        if(L->ini == NULL)
        {
            L->ini = L->fim = novo;
        }
        else
        {
            novo->ant = L->fim;
            L->fim->prox = novo;
            L->fim = novo;
        }
    }
    return L;
}

Nod* localiza_elemento(Listad *L, int valor)
{

    Nod* aux = L->ini;

    while(aux!=NULL && aux->info != valor)
        aux = aux->prox;

    return aux;
}


void insere_apos_elemento(Listad* L, int valor, int elemento)
{
    Nod* novo =cria_nod(valor);

    Nod *aux2, *aux = localiza_elemento(L, elemento);

    if (aux != NULL)
    {
        aux2 = aux->prox;
        novo->prox = aux2;
        aux2->ant = novo;
        novo->ant = aux;
        aux->prox = novo;
        if (aux == L->fim)
            L->fim = novo;
    }
    else
        printf("elemento nao encontrado");
}

int remove_inicio_listad(Listad *L)
{
    Nod* aux;
    int resposta = -1;//quando nao tem nada pra remover
    if (L!=NULL)
        if (L->ini != NULL)
        {
            aux = L->ini;

            if (L->ini != L->fim)
            {
                L->ini->prox->ant = NULL;
                L->ini = L->ini->prox;
            }
            else
                L->ini = L->fim = NULL;

            resposta = aux->info;
            free(aux);
        }
    return resposta;
}

int remove_fim_listad(Listad *L)
{
    Nod* aux;
    int resposta = -1;

    if(L != NULL && L->fim != NULL)
    {
        aux = L->fim;
        if(L->ini != L->fim)//mais de um elemento na lista
        {
            L->fim->ant->prox = NULL;
            L->fim = L->fim->ant;
        }
        else//s� tem um elemento na lista
            L->ini = L->fim = NULL;

        resposta = aux->info;
        free(aux);
    }
    return resposta;
}

int remove_elemento_listad(Listad *L, int valor)
{
    Nod *aux = localiza_elemento(L,valor);
    int resposta = -1;

    if (aux != NULL)
    {
        if (aux == L->ini)
            resposta = remove_inicio_listad(L);
        else if(aux == L->fim)
            resposta = remove_fim_listad(L);
        else
        {
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
            resposta = aux->info;
            free(aux);
        }
    }
    return resposta;
}

Listad* libera_listad(Listad *L)
{
    Nod *aux = L->ini;

    while (aux != NULL)
    {
        L->ini = L->ini->prox;
        free(aux);
        aux = L;
    }

    free(L);
    return NULL;

}

/*FIm B. ListaDupla*/

/*Minhas funções*/

Listad* ArvoreForListad(No* raiz, Listad* lista) {

    if(raiz != NULL) {
         
    }

}

/*Fim minhas funçõse*/


int main(int argc, char const *argv[])
{
    int info = 0;
    No* arvore = NULL;
    Listad* listaDupla = NULL;

    while (info != -1)
    {
        printf("->");
        scanf("%i", &info);
        if(info != -1) {
            arvore = abb_insere(arvore, info);
        }
    }
    
    abb_em_ordem(arvore);

    abb_libera(arvore);

    return 0;
}
