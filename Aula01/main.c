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
    void* info;
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

Nod* cria_nod(void* valor)
{
    Nod* novo = (Nod*)malloc(sizeof(Nod));
    novo->ant = novo->prox = NULL;
    novo->info = valor;
    return novo;
}


Listad* insere_inicio_listad(Listad *L, void* valor)
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


Listad* insere_fim_listad(Listad* L, void* valor)
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



void* remove_inicio_listad(Listad *L)
{
    Nod* aux;
    void* resposta = NULL;//quando nao tem nada pra remover
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

void* remove_fim_listad(Listad *L)
{
    Nod* aux;
    void* resposta = NULL;

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

Listad* libera_listad(Listad *L)
{
    Nod *aux = L->ini;

    while (aux != NULL)
    {
        L->ini = L->ini->prox;
        free(aux->info);
        free(aux);
        aux = L->ini;
    }

    free(L);
    return NULL;
}

int eh_vazia_listad(Listad *L)
{
    if (L == NULL || L->ini == NULL)
        return 1;
    else
        return 0;
}


/*FIm B. ListaDupla*/

/*B. listaSimples*/

struct noS
{
    int info;
    struct noS *prox;
    int size;
};

typedef struct noS NoS;

NoS* cria_noS(int valor)
{
    NoS* novo;
    novo = (NoS*) malloc(sizeof(NoS));

//inicializar campos
    novo->prox = NULL;
    novo->info = valor;
    novo->size = 0;

    return novo;
}


NoS* insere_inicio(NoS *L, int valor)
{
    NoS* nuevo = cria_noS(valor);
    if (L != NULL)
    {
        nuevo->prox = L;
    }

    L->size += 1;

    return nuevo;
}


void mostra_lista(NoS* L)
{
    NoS* aux = L;

    while (aux != NULL)
    {
        printf("%i ", aux->info);
        aux = aux->prox;// (*aux).prox
    }
    printf("\n");
}



NoS* libera_lista(NoS *L)
{
    NoS *aux = L;

    while (aux != NULL)
    {
        L = L->prox;
        free(aux);
        aux = L;
    }
    return NULL;
}

NoS* insere_fim(NoS* L, int valor)
{
    NoS* novo = cria_noS(valor);
    NoS* aux = L;

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

    L->size++;

    return L;
}

//insere ap�s o elemento

NoS* insere_meio(NoS* L, int elemento, int valor)
{

    NoS* aux = L;
    NoS* novo = cria_noS(valor);

    if (L == NULL)
    {
        L = novo;
    }
    else
    {
        while (aux->info != elemento)
        {
            aux = aux->prox;
        }
        novo->prox = aux->prox;
        aux->prox = novo;
    }
    return L;
}

NoS* remove_elemento(NoS* L, int elemento)
{

    NoS* aux = L;
    NoS* anterior = NULL;
    if (L != NULL)
    {
        while (aux->info != elemento)
        {
            anterior = aux;
            aux = aux->prox;
        }
        if (anterior == NULL)//remove o primeiro elemento
        {
            L = aux->prox;
        }
        else
        {
            anterior->prox = aux->prox;
        }
        free(aux);
    }
    return L;//se nao removeu o primeiro elemento, retorna o mesmmo L
}

int remove_inicio(NoS** L)
{
    NoS* aux = *L;
    int pont;

    if (*L != NULL)
    {
        *L = aux->prox;
    }
    pont = aux->info;
    free(aux);
    return pont;
}


/*FIM B. listaSimples*/

/*B. Pilha*/

typedef NoS Pilha;

Pilha* cria_pilha()
{
    Pilha *p = NULL;
    return p;
}

Pilha* push(Pilha *p, int elemento)
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
int pop(Pilha **p)
{
    Pilha *pont = *p;
    int resposta = -1;
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



int top(Pilha *p)
{
    if (!eh_vazia_pilha(p))
        return p->info;
    else
        return -1;
}

/*FIM B. Pilha*/

// Listad* ArvoreForListad(No* raiz, Listad* lista) {

//     if(raiz != NULL) {
//         ArvoreForListad(raiz->esq, lista);
//         lista = insere_fim_listad(lista, (void*)raiz->info);
//         ArvoreForListad(raiz->dir, lista);     
//     }

//     return lista;

// }

void *get(Pilha *l, int index) {
    Pilha *n = l;
    int i = 0;
    while (n != NULL) {
        if (i == index) {
            return n->info;
        }
        n = n->prox;
        i++;
    }
    return NULL;
}

void em_ordem_iterativo(No* raiz) {

    Pilha* pilha = cria_pilha();
    No* aux = raiz;

    do{

        while (aux != NULL)
        {
            pilha = insere_fim(pilha, aux->info);
            aux = aux->esq;
        }
        
        // verifica se ja processou toda a arvore
        if(!eh_vazia_pilha(pilha)) {
            pop(&pilha);
            printf("%i", aux->info);
            aux = aux->dir;
        }

    } while(aux != NULL || !eh_vazia_pilha(pilha));

}

Listad* MostrarListaInt(Listad* lista) {

    Nod* aux = lista->ini;

    while (aux != NULL)
    {
        printf("%i ", aux->info);
        aux = aux->prox;
    }
    
    printf("\n");

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

    // listaDupla = ArvoreForListad(arvore, listaDupla);
    
    printf("\n\nArvore -> ");

    em_ordem_iterativo(arvore);

    // printf("\n\nLista dupla -> ");

    // MostrarListaInt(listaDupla);

    abb_libera(arvore);

    printf("\n\n");

    return 0;
}
