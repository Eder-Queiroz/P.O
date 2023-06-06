/* 
@Kiwiabacaxi 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100

// grafos com matriz de adjacencia
// -------------------- // GRAFOS // -------------------- //
// struct de um grafo

typedef struct {
    char nome[20];
    int amigos[MAX];
    int n_amigos;
    int attr;
} Pessoa;

typedef struct {
    Pessoa pessoa[MAX];
    int** matriz;
    int num_vertices;
} Grafo;

// funcao que cria um grafo vazio
Grafo* cria_grafo(int num_vertices) {
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));
    g->num_vertices = num_vertices;
    g->matriz = (int**) malloc(num_vertices * sizeof(int*));
    int i, j;
    for (i = 0; i < num_vertices; i++) {
        g->matriz[i] = (int*) malloc(num_vertices * sizeof(int));
        for (j = 0; j < num_vertices; j++) {
            g->matriz[i][j] = 0;
        }
    }
    return g;
}

// funcao que insere uma aresta no grafo
void insere_aresta(Grafo* g, int v1, int v2) {
    g->matriz[v1][v2] = 1;
}

// funcao que remove uma aresta do grafo
void remove_aresta(Grafo* g, int v1, int v2) {
    g->matriz[v1][v2] = 0;
}

// funcao que verifica se existe uma aresta entre dois vertices
int existe_aresta(Grafo* g, int v1, int v2) {
    return g->matriz[v1][v2] == 1;
}

// funcao que imprime o grafo
void imprime_grafo(Grafo* g) {
    int i, j;
    for (i = 0; i < g->num_vertices; i++) {
        printf("%d: ", i);
        for (j = 0; j < g->num_vertices; j++) {
            if (g->matriz[i][j] == 1) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}

// funcao que printa a matriz de adjacencia
void imprime_matriz(Grafo* g) {
    int i, j;
    for (i = 0; i < g->num_vertices; i++) {
        for (j = 0; j < g->num_vertices; j++) {
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

// funcao que libera a memoria alocada para o grafo
void libera_grafo(Grafo* g) {
    int i;
    for (i = 0; i < g->num_vertices; i++) {
        free(g->matriz[i]);
    }
    free(g->matriz);
    free(g);
}

// -------------------- // FILA // -------------------- //
// struct de uma fila
typedef struct no {
    int vertice;
    struct no* prox;
} No;

typedef struct {
    No* inicio;
    No* fim;
} Fila;

// funcoes da fila
// cria uma fila vazia
Fila* cria_fila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

// insere um elemento no fim da fila
void insere_fila(Fila* f, int vertice) {
    No* novo = (No*) malloc(sizeof(No));
    novo->vertice = vertice;
    novo->prox = NULL;
    if (f->fim != NULL) {
        f->fim->prox = novo;
    } else {
        f->inicio = novo;
    }
    f->fim = novo;
}

// remove um elemento do inicio da fila
int remove_fila(Fila* f) {
    if (f->inicio != NULL) {
        No* removido = f->inicio;
        int vertice = removido->vertice;
        f->inicio = removido->prox;
        if (f->inicio == NULL) {
            f->fim = NULL;
        }
        free(removido);
        return vertice;
    }
    return -1;
}

// verifica se a fila esta vazia
int fila_vazia(Fila* f) {
    return f->inicio == NULL;
}

// libera a memoria alocada pela fila
void libera_fila(Fila* f) {
    No* atual = f->inicio;
    while (atual != NULL) {
        No* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(f);
}


// -------------------- // BFS // -------------------- //
// bfs sem fila
void bfs(Grafo* g, int inicio) {
    int i, j;
    int* visitados = (int*) malloc(g->num_vertices * sizeof(int));
    for (i = 0; i < g->num_vertices; i++) {
        visitados[i] = 0;
    }
    visitados[inicio] = 1;
    printf("%d ", inicio);
    for (i = 0; i < g->num_vertices; i++) {
        if (g->matriz[inicio][i] == 1 && !visitados[i]) {
            visitados[i] = 1;
            printf("%d ", i);
            for (j = 0; j < g->num_vertices; j++) {
                if (g->matriz[i][j] == 1 && !visitados[j]) {
                    visitados[j] = 1;
                    printf("%d ", j);
                }
            }
        }
    }
    free(visitados);
}

// bfs com fila
void bfs_fila(Grafo* g, int inicio) {
    int i;
    int* visitados = (int*) malloc(g->num_vertices * sizeof(int));
    for (i = 0; i < g->num_vertices; i++) {
        visitados[i] = 0;
    }
    Fila* f = cria_fila();
    insere_fila(f, inicio);
    visitados[inicio] = 1;
    while (!fila_vazia(f)) {
        int vertice = remove_fila(f);
        printf("%d ", vertice);
        for (i = 0; i < g->num_vertices; i++) {
            if (g->matriz[vertice][i] == 1 && !visitados[i]) {
                insere_fila(f, i);
                visitados[i] = 1;
            }
        }
    }
    free(visitados);
    libera_fila(f);
}

// funcao que retorna um bool se existe caminho de origem para destino, usando busca em largura
// funcao do tipo bool que retorna true se existe caminho de origem para destino, usando busca em largura
bool existe_caminho(Grafo* g, int origem, int destino) {
    int i;
    int* visitados = (int*) malloc(g->num_vertices * sizeof(int));
    for (i = 0; i < g->num_vertices; i++) {
        visitados[i] = 0;
    }
    Fila* f = cria_fila();
    insere_fila(f, origem);
    visitados[origem] = 1;
    while (!fila_vazia(f)) {
        int vertice = remove_fila(f);
        if (vertice == destino) {
            free(visitados);
            libera_fila(f);
            return true;
        }
        for (i = 0; i < g->num_vertices; i++) {
            if (g->matriz[vertice][i] == 1 && !visitados[i]) {
                insere_fila(f, i);
                visitados[i] = 1;
            }
        }
    }
    free(visitados);
    libera_fila(f);
    return false;
}

// -------------------- // DFS // -------------------- //
// dfs recursivo
void dfs(Grafo* g, int inicio, int* visitados) {
    int i;
    visitados[inicio] = 1;
    printf("%d ", inicio);
    for (i = 0; i < g->num_vertices; i++) {
        if (g->matriz[inicio][i] == 1 && !visitados[i]) {
            dfs(g, i, visitados);
        }
    }
}

// dfs iterativo
void dfs_iterativo(Grafo* g, int inicio) {
    int i;
    int* visitados = (int*) malloc(g->num_vertices * sizeof(int));
    for (i = 0; i < g->num_vertices; i++) {
        visitados[i] = 0;
    }
    Fila* f = cria_fila();
    insere_fila(f, inicio);
    visitados[inicio] = 1;
    while (!fila_vazia(f)) {
        int vertice = remove_fila(f);
        printf("%d ", vertice);
        for (i = 0; i < g->num_vertices; i++) {
            if (g->matriz[vertice][i] == 1 && !visitados[i]) {
                insere_fila(f, i);
                visitados[i] = 1;
            }
        }
    }
    free(visitados);
    libera_fila(f);
}

// funcao que do tipo bool que retorna true se existe caminho de origem para destino, usando busca em profundidade
bool existe_caminho_dfs(Grafo* g, int origem, int destino) {
    int i;
    int* visitados = (int*) malloc(g->num_vertices * sizeof(int));
    for (i = 0; i < g->num_vertices; i++) {
        visitados[i] = 0;
    }
    Fila* f = cria_fila();
    insere_fila(f, origem);
    visitados[origem] = 1;
    while (!fila_vazia(f)) {
        int vertice = remove_fila(f);
        if (vertice == destino) {
            free(visitados);
            libera_fila(f);
            return true;
        }
        for (i = 0; i < g->num_vertices; i++) {
            if (g->matriz[vertice][i] == 1 && !visitados[i]) {
                insere_fila(f, i);
                visitados[i] = 1;
            }
        }
    }
    free(visitados);
    libera_fila(f);
    return false;
}

// -------------------- // MAIN // -------------------- //
/* 
Restrições

3 <= E <= 100
E − 1 <= L <= E × (E − 1)/2 
*/

int main(){
    Grafo *g = cria_grafo(2);
    int x = -1, y = -1, i = 0, n = -1, count = 0;
    char spam[MAX][6];


    do{

        scanf("%i", &n);

        if(n != 0) {

            for(i = 0; i < n; i++) {

                while(x != 0) {
                    scanf("%i", &x);
                    if(x != 0) {
                        insere_aresta(g, i, x - 1);
                    }
                }

            }

            while (y != 0 ) {
                scanf("%s", &spam[count][0]);

                y = spam[count][0];
                
                if(spam[count][0] != "0") {

                    scanf("%s %s %s %s %s", &spam[count][1], &spam[count][2], &spam[count][3], &spam[count][4], &spam[count][5]);

                }

                count++;
            }

            

        }

    }while(n != 0);

    return 0;
}