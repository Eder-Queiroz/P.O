#include <stdio.h>
#include <stdlib.h>

struct noavl
{
    int info;
    int fb;
    struct noavl *esq, *dir;
    //struct noavl *pai;
};

typedef struct noavl Noavl;

void libera_avl(Noavl* raiz);
int em_ordem(Noavl* raiz, int flag);
void recalcula_fb(Noavl *candidato,int info);
Noavl *insere_noavl(Noavl *tree, int info, Noavl **pai_candidato);
Noavl *insercao_geral(Noavl *tree,int info);
Noavl *cria_noavl(int info);

int main(int argc, char const *argv[])
{
    
    int n = 0, info = 0, flag = 0, i = 0;
    Noavl* tree = NULL;

    // printf("Insere quantidade de arvores -> ");
    scanf("%i", &n);


    for(i = 0; i < n; i++) {


        while (info != -1)
        {
            // printf("insere info -> ");
            scanf("%i", &info);

            if(info != -1) {

                tree = insercao_geral(tree, info);

            }

        }
        
        flag = em_ordem(tree, flag);

        if(flag == 1) {
            printf("nao");
        }else {
            printf("sim");
        }

        printf("\n");

        flag = 0;
        info = 0;

        libera_avl(tree);
        tree = NULL;
    }
    

    return 0;
}

// arvore AVL

Noavl *cria_noavl(int info)
{
    Noavl *novo = (Noavl *)malloc(sizeof(Noavl));
    novo->dir = novo->esq = NULL;
    novo->info = info;
    novo->fb = 0;

    return novo;
}

Noavl *insercao_geral(Noavl *tree,
                      int info)
{
    Noavl *candidato = NULL;
    Noavl *pai_candidato = NULL;

    if (tree == NULL)
    {
        return cria_noavl(info);
    }
    else
    {
        candidato = insere_noavl(tree, info, &pai_candidato);
        recalcula_fb(candidato, info);
    }
    return tree;
}

Noavl *insere_noavl(Noavl *tree, int info, Noavl **pai_candidato)
{
    Noavl *aux = tree;
    Noavl *pai_aux = NULL;
    Noavl *novo = cria_noavl(info);
    Noavl *candidato = tree;

    while (aux != NULL)
    {
        if (aux->fb != 0)
        {
            candidato = aux;
            *pai_candidato = pai_aux;
        }
        pai_aux = aux;
        if (info < aux->info)
            aux = aux->esq;
        else
            aux = aux->dir;
    }
    if (info < pai_aux->info)
        pai_aux->esq = novo;
    else
        pai_aux->dir = novo;

    return candidato;
}

void recalcula_fb(Noavl *candidato,
                  int info)
{
    Noavl *aux = candidato;
    while (aux->info != info)
    {
        if (info < aux->info)
        {
            aux->fb++;
            aux = aux->esq;
        }
        else
        {
            aux->fb--;
            aux = aux->dir;
        }
    }
}
//retorna a nova raiz da subarvore 

int em_ordem(Noavl* raiz, int flag)
{

    if (raiz != NULL)
    {
        flag = em_ordem(raiz->esq, flag);
        if(raiz->fb >= 2 || raiz->fb <= -2) {
            flag = 1;
        }
        // printf("%i ", raiz->fb);
        // printf("(%i) ", raiz->info);
        flag = em_ordem(raiz->dir, flag);
    }

    return flag;
}

void libera_avl(Noavl* raiz)
{

        if (raiz != NULL)
        {
            libera_avl(raiz->esq);
            libera_avl(raiz->dir);
            free(raiz);
        }
}

// Eder Queiroz
// Carlos Alexandre