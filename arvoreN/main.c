#include <stdlib.h>
#include <stdio.h>

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

struct tree {
    int valor;
    int quantidade;
    Listad* L;
};

typedef struct tree Tree;

// LISTA DUPLA
Listad* cria_listad();
Nod* cria_nod(void* valor);
Listad* insere_inicio_listad(Listad *L, void* valor);
Listad* insere_fim_listad(Listad *L, void* valor);
void* remove_fim_listas(Listad *L);
void* remove_inicio_listad(Listad *L);
Listad* libera_listad(Listad *L);
int eh_vazia_listad(Listad *L);

// tree
Tree* cria_tree();
Tree* insere_arvore(Tree* tree, int valor, int quantidadeFilho);

int main(int argc, char const *argv[])
{
    
    return 0;
}

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

Tree* cria_tree() {
    Tree* newTree;
    newTree = (Tree*)malloc(sizeof(Tree));
    newTree->L = NULL;
    newTree->quantidade = 0;
    newTree->valor = 1;
    return newTree;
}

Tree* insere_arvore(Tree* tree, int valor, int quantidadeFilho) {

    if(tree == NULL) {

        tree = cria_tree();
        tree->L = insere_fim_listad(tree->L, (int*)valor);
        tree->quantidade = quantidadeFilho;
    }

    return tree;

}