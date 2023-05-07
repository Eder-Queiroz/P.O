#ifndef arvoreb_h
#define arvoreb_h

#include <stdio.h>
#include <stdlib.h>
#include "listadupla.h"
#include <math.h>
#include <windows.h>
#include "fila.h"

struct nob
{
    int folha; //1 se for folha, 0 caso contrario
    int qtd_chaves;
    struct nob* pai;
    Listad *lista_chaves;
};

typedef struct nob Nob;

typedef struct arvoreb
{
    Nob *raiz;
    int ordem;
    int altura;
}Arvoreb;

typedef struct chave
{
    int valor_chave;
    Nob *filho;
} Chave;


void insercao_arvoreb(Arvoreb *tree, int chave);
Nob *localiza_folha(Arvoreb *tree, int chave);
Arvoreb* cria_arvoreb(int ordem);
Nob* cria_nob();
Listad* insere_ordenado_listad(Listad* lista_nos,
                     Chave *chave_nova);
Chave *cria_chave(int valor);
Listad *divide_lista(Listad *L, int n);
int get_valor_chave(Nod *aux);
Nob *get_filho(Nod *aux);
void set_filho(Nod *aux, Nob *novo_filho);
Chave *remove_ultima_chave(Nob *folha);
Listad *insere_primeira_chave(Listad *L, void *ch);

Nob *divide_no(Nob *no_dividir);
void em_ordem(Nob *raiz);
void mostra_nob(Nob *raiz, int detalhe);
Arvoreb *libera_arvoreb(Arvoreb *T);
Nob *libera_nob(Nob *raiz);
Nob *cria_nova_raiz(Chave *chave_a_subir, Nob *no_insercao, Nob *novo );
void percurso_em_nivel_posicionado(Arvoreb *T);
void em_nivel_posicionado(Fila *f, int nivel, int largura_tela);
void gotoxy(int x, int y);
#endif