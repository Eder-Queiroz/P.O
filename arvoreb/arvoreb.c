#include "arvoreB.h"

Arvoreb* cria_arvoreb(int ordem)
{
    Arvoreb *nova=(Arvoreb*)malloc(sizeof(Arvoreb));

    nova->raiz = NULL;
    nova->ordem = ordem;
    nova->altura = 0;
    return nova;
}

Nob* cria_nob()
{
    Nob *novo=(Nob*)malloc(sizeof(Nob)), novo2;

    novo->folha = 1;
    novo->pai = NULL;
    novo->qtd_chaves = 0;
    novo->lista_chaves = cria_listad();
   
    return novo;
}

Listad* dividir(Listad* L, int n) {

    int i = 0;
    Nod* aux = L->ini;
    Listad* novaLista = cria_listad();
    novaLista->fim = L->fim;

    for(i = 1; i <= n; i++) {

        if(i == n) {
            L->fim = aux->ant;
            L->fim->prox = NULL;

            novaLista->ini = aux;
            novaLista->ini->ant = NULL;

        }

        aux = aux->prox;

    }    

    return novaLista;

}

Listad* insere_lista_emordem(Listad* L, Chave* chave) {

    Nod* novoNod = cria_nod((void*)chave);

    if(L == NULL) {

        L = cria_listad();
        L->fim = L->ini = novoNod;

    }else {

        Nod* aux = L->ini;
        int flag = 0;

        if(chave->valor_chave < ((Chave*)L->ini->info)->valor_chave) {

            L = insere_inicio_listad(L, (void*)chave);
         
        } else if(chave->valor_chave > ((Chave*)L->fim->info)->valor_chave) {

            L = insere_fim_listad(L, (void*)chave);
          
        } else {

             while (((Chave*)aux->info)->valor_chave < chave->valor_chave) {
                    
                aux = aux->prox;

            }
            
            novoNod->ant = aux;
            novoNod->prox = aux->prox;
            aux->prox->ant = novoNod;
            aux->prox = novoNod;


        }
         

    }

    return L;

}