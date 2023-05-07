#ifndef arvorebplus_h
#define arvorebplus_h
// #include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registro
{
    int valor;
} Registro;

// Node
typedef struct node
{
    void **ponteiro;
    int *chave;
    struct node *pai;
    int eh_folha;
    int num_chave;
    struct node *prox;
} Node;

void inserir_fila(Node *new_node);
Node *desenfileirar(void);

int caminhoFolha(Node *const raiz, Node *filho);

void printArvore(Node *const raiz);
Node *encontrarFolha(Node *const raiz, int chave, int verbose);
Registro *encontrar(Node *raiz, int chave, int verbose, Node **fora_folha);
int cut(int length);

Registro *criarRegistro(int valor);
Node *criaNode(void);
Node *criaFolha(void);
int getIndiceEsquerda(Node *pai, Node *esquerda);
Node *inserirFolha(Node *folha, int chave, Registro *ponteiro);
Node *inserirFolhaAposDivisao(Node *raiz, Node *folha, int chave, Registro *ponteiro);
Node *inserirNode(Node *raiz, Node *pai, int indice_esquerda, int chave, Node *direita);
Node *inserirNodeAposDivisao(Node *raiz, Node *pai, int indice_esquerda, int chave, Node *direita);
Node *inserirPai(Node *raiz, Node *esquerda, int chave, Node *direita);
Node *inserirNovaRaiz(Node *esquerda, int chave, Node *direita);
Node *iniciarNovaArvore(int chave, Registro *ponteiro);
Node *inserir(Node *raiz, int chave, int valor);

#endif