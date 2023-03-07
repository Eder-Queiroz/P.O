#include "arvore_avl.h"

Noavl* cria_noavl(int info)
{
    Noavl* novo = (Noavl*) malloc(sizeof(Noavl));
    novo->dir=novo->esq = NULL;
    novo->info = info;
    novo->fb = 0;

    return novo;
}

Noavl* insercao_geral(Noavl* tree, 
                        int info)
{
    Noavl* candidato=NULL;
    Noavl* pai_candidato = NULL;
    
    if (tree == NULL)
    {
        return cria_noavl(info);
    }
    else
    {
        candidato = insere_no(tree, info, &pai_candidato);
        recalcula_fb(candidato, info);
        if(candidato->fb == -2 || candidato->fb == +2)
        {
            if (candidato == tree)
                tree = rotacao_geral(candidato);
            else
                if(pai_candidato->esq == candidato)
                    pai_candidato->esq = rotacao_geral(candidato);
                else
                    pai_candidato->dir = rotacao_geral(candidato);
            recalculo_final_fb(candidato);

        }    
    }
return tree;

}

Noavl* insere_no(Noavl* tree, int info, Noavl** pai_candidato)
{
    Noavl* aux = tree;
    Noavl* pai_aux = NULL;
    Noavl* novo = cria_noavl(info);
    Noavl* candidato = NULL;

    while(aux != NULL)
    {
        if (aux->fb != 0)
        {
               candidato = aux;
               *pai_candidato = pai_aux;
        }
        pai_aux = aux;
        if (info < aux->info)
            aux=aux->esq;
        else
            aux=aux->dir;
    }
    if(info < pai_aux->info)
        pai_aux->esq = novo;
    else
        pai_aux->dir = novo;

    return candidato;
}

void recalcula_fb(Noavl* candidato, int info)
{

    Noavl* aux = candidato;

    while(aux->info != info) {

        if(info > aux->info) {
            aux->fb--;
            aux = aux->dir;
        }else {
            aux->fb++;
            aux = aux->esq;
        }

    }

}

Noavl* rotacao_geral(Noavl*candidato) {
    Noavl*nova_raiz = NULL;
    if(candidato->fb == +2) {
        if(candidato->esq->fb == +1) {
            nova_raiz = rotacao_direita(candidato);
        } else {
            nova_raiz = rotacao_esquerda_direita(candidato);
        }
    }else {
        if(candidato->dir->fb == -1) {
            nova_raiz = rotacao_esquerda(candidato);
        }else {
            nova_raiz = rotacao_direita_esquerda(candidato);
        }
    }

    return nova_raiz;

}

Noavl*rotacao_direita(Noavl*candidato) {

    Noavl* filho = candidato->esq;
    Noavl* neto = filho->dir;
    filho->dir = candidato;
    candidato->esq = neto;

    return filho;

}

Noavl*rotacao_esquerda(Noavl*candidato) {
    Noavl* filho = candidato->dir;
    Noavl* neto = filho->esq;
    filho->esq = candidato;
    candidato->dir = neto;

    return filho;
}

Noavl* rotacao_direita_esquerda(Noavl* candidato) {

    candidato->dir = rotacao_direita(candidato->dir);
    candidato = rotacao_esquerda(candidato);

    return candidato;

}

Noavl* rotacao_esquerda_direita(Noavl* candidato) {

    candidato->esq = rotacao_esquerda(candidato->esq);
    candidato = rotacao_direita(candidato);

    return candidato;

}