#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct nod
{
    char nome[21];
    int T;
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

typedef struct atr
{
    char atr[21];
    int Peso;
    int valor;
    struct atr *prox;
} Atr;

typedef struct spam
{
    Atr *atributo;
    int *verificacao;
    struct spam *prox;

} Spam;

typedef struct grafo
{
    int ordem;
    int **adjacencias;
    int *visitados;
    Listad *nomes;
    Spam *atributos;
} Grafo;

// LISTA
Listad *cria_listad();
Nod *cria_nod(char valor[], int T);
Listad *insere_fim_listad(Listad *L, char valor[], int T);

//  GRAFO
Grafo *cria_grafo(int n);
void mostra_grafo(Grafo *g);
void dfs(Grafo *grafo, int p);
Spam *cria_spam();
Spam *insere_fim_spam(Spam *L, char atr1[], char atr2[], char atr3[], int valor, int t1, int t2, int t3);
Atr *cria_atr(char atr[], int peso, int valor);
Atr *insere_fim(Atr *L, char atr[], int peso, int valor);
void mostra_lista(Atr *L);

int main(int argc, char const *argv[])
{
    int N = 0, C = 0, T1 = 0, T2 = 0, T3 = 0, Count = 0, T = 0, amigos = 0;
    int i = 0, j = 0;
    char nome[21];
    char Atr1[21], Atr2[21], Atr3[21];
    Grafo *g = NULL;

    do
    {
        scanf("%d", &N);
        g = cria_grafo(N);

        for (i = 0; i < N; i++)
        {
            do
            {
                scanf("%d", &C);
                if (C != 0)
                {
                    g->adjacencias[i][C - 1] = 1; // montando matriz de adjacências
                }

            } while (C != 0);
        }

        do
        {
            scanf("%d", &T1);

            if (T1 != 0)
            {
                scanf("%d %d", &T2, &T3);
                scanf("%s %s %s", Atr1, Atr2, Atr3);

                g->atributos = insere_fim_spam(g->atributos, Atr1, Atr2, Atr3, Count, T1, T2, T3);

                // g->atributos = insere_fim(g->atributos, Atr1, T1, Count);
                // g->atributos = insere_fim(g->atributos, Atr2, T2, Count);
                // g->atributos = insere_fim(g->atributos, Atr3, T3, Count);

                Count++;
            }

        } while (T1 != 0);

        // for (i = 0; i < N; i++)
        // {
        //     for (j = 0; j < N; j++)
        //     {
        //         if (g->adjacencias[i][j] == 1)
        //         {
        //             T++;
        //         }
        //     }
        //     scanf("%s", nome);
        //     g->nomes = insere_fim_listad(g->nomes, nome, T);
        //     T = 0;
        // }

        for (i = 0; i < N; i++)
        {

            Spam *aux = g->atributos;

            for (j = 0; j < N; j++)
            {

                if (g->adjacencias[i][j] == 1)
                {
                    amigos++;
                }
            }

            scanf("%s", nome);
            printf("%s: ", nome);

            while (aux != NULL)
            {
                // printf("%i %i %i \n", aux->verificacao[0], aux->verificacao[1], aux->verificacao[2]);

                if (amigos < aux->verificacao[1])
                {
                    printf("%s ", aux->atributo->atr);
                }
                else if (aux->verificacao[1] <= amigos && amigos < aux->verificacao[2])
                {
                    printf("%s ", aux->atributo->prox->atr);
                }
                else if (aux->verificacao[2] <= amigos)
                {
                    printf("%s ", aux->atributo->prox->prox->atr);
                }

                aux = aux->prox;
            }

            printf("\n");
            // printf("\n\n%i\n\n", amigos);
            amigos = 0;
        }

        // mostra_grafo(g);

        Count = 0;

        free(g);

    } while (N != 0);

    return 0;
}

Listad *cria_listad()
{
    Listad *novalista;
    novalista = (Listad *)malloc(sizeof(Listad));
    novalista->ini = novalista->fim = NULL;
    return novalista;
}

Nod *cria_nod(char valor[], int T)
{
    Nod *novo = (Nod *)malloc(sizeof(Nod));
    novo->ant = novo->prox = NULL;
    strcpy(novo->nome, valor);
    novo->T = T;
    return novo;
}

Listad *insere_fim_listad(Listad *L, char valor[], int T)
{
    Nod *novo = cria_nod(valor, T);

    if (L == NULL)
    {
        L = cria_listad();
        L->ini = L->fim = novo;
    }
    else
    {

        if (L->ini == NULL)
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

Grafo *cria_grafo(int n)
{
    int i, j;
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));
    g->ordem = n;
    g->visitados = (int *)calloc(n, sizeof(int));
    g->nomes = cria_listad();
    g->atributos = NULL;
    g->adjacencias = (int **)malloc(sizeof(int *) * n);
    for (i = 0; i < n; i++)
        g->adjacencias[i] = (int *)malloc(sizeof(int) * n);

    return g;
}

// void mostra_grafo(Grafo *g)
// {
//     int i, j, fileira = -1;
//     Nod *aux = g->nomes->ini;
//     Atr *aux2 = g->atributos;

//     while (aux != NULL)
//     {

//         printf("%s: ", aux->nome);

//         while (aux2 != NULL)
//         {
//             if (aux->T <= aux2->Peso && fileira != aux2->valor)
//             {
//                 printf("%s ", aux2->atr);
//                 fileira = aux2->valor;
//             }
//         }

//         aux2 = g->atributos;
//         fileira = -1;
//         aux = aux->prox;

//         printf("\n");
//     }
// }

void dfs(Grafo *grafo, int p)
{
    if (grafo->visitados[p])
        return;
    grafo->visitados[p] = 1;
    for (int i = 0; i < grafo->ordem; i++)
    {
        if (grafo->adjacencias[p][i])
        {
            dfs(grafo, i);
        }
    }
}

Spam *cria_spam()
{
    Spam *novo;
    novo = (Spam *)malloc(sizeof(Spam));
    novo->prox = NULL;
    novo->verificacao = (int *)calloc(3, sizeof(int));
    novo->atributo = NULL;
}

Atr *cria_atr(char atr[], int peso, int valor)
{
    Atr *novo;
    novo = (Atr *)malloc(sizeof(Atr));
    novo->prox = NULL;
    novo->valor = valor;
    novo->Peso = peso;
    strcpy(novo->atr, atr);
    return novo;
}

Spam *insere_fim_spam(Spam *L, char atr1[], char atr2[], char atr3[], int valor, int t1, int t2, int t3)
{

    Spam *novo = cria_spam();
    novo->verificacao[0] = t1;
    novo->verificacao[1] = t2;
    novo->verificacao[2] = t3;
    novo->atributo = insere_fim(novo->atributo, atr1, t1, valor);
    novo->atributo = insere_fim(novo->atributo, atr2, t2, valor);
    novo->atributo = insere_fim(novo->atributo, atr3, t3, valor);
    Spam *aux = L;

    if (L == NULL)
    {
        L = novo;
    }
    else
    {

        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    return L;
}

Atr *insere_fim(Atr *L, char atr[], int peso, int valor)
{
    Atr *novo = cria_atr(atr, peso, valor);
    Atr *aux = L;

    if (L == NULL)
    {
        L = novo;
    }
    else
    {

        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
    return L;
}
