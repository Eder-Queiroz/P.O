#include "arvorebplus.h"

#define ORDER 3
Node *queue = NULL;

void inserir_fila(Node *novo_no)
{
    Node *c;
    if (queue == NULL)
    {
        queue = novo_no;
        queue->prox = NULL;
    }
    else
    {
        c = queue;
        while (c->prox != NULL)
        {
            c = c->prox;
        }
        c->prox = novo_no;
        novo_no->prox = NULL;
    }
}

Node *desenfileirar(void)
{
    Node *n = queue;
    queue = queue->prox;
    n->prox = NULL;
    return n;
}

int caminhoFolha(Node *const raiz, Node *filho)
{
    int tamanho = 0;
    Node *c = filho;
    while (c != raiz)
    {
        c = c->pai;
        tamanho++;
    }
    return tamanho;
}

void printArvore(Node *const raiz)
{

    Node *n = NULL;
    int i = 0;
    int ranque = 0;
    int novo_ranque = 0;

    if (raiz == NULL)
    {
        printf("Arvore vazia\n");
        return;
    }

    queue = NULL;
    inserir_fila(raiz);

    while (queue != NULL)
    {
        n = desenfileirar();
        if (n->pai != NULL && n == n->pai->ponteiro[0])
        {
            novo_ranque = caminhoFolha(raiz, n);
            if (novo_ranque != ranque)
            {
                ranque = novo_ranque;
                printf("\n");
            }
        }
        for (i = 0; i < n->num_chave; i++)
        {
            printf("%d ", n->chave[i]);
        }
        if (!n->eh_folha == 1)
        {
            for (i = 0; i <= n->num_chave; i++)
            {
                inserir_fila(n->ponteiro[i]);
            }
        }
        printf("| ");
    }
    printf("\n");
}

Node *encontrarFolha(Node *const raiz, int chave, int verbose)
{

    if (raiz == NULL)
    {

        if (verbose == 1)
        {
            printf("Arvore vazia.\n");
        }

        return raiz;
    }

    int i = 0;
    Node *c = raiz;

    while (!c->eh_folha)
    {
        if (verbose == 1)
        {
            printf("[");
            for (i = 0; i < c->num_chave - 1; i++)
            {
                printf("%d ", c->chave[i]);
            }
            printf("%d] ", c->chave[i]);
        }

        i = 0;
        while (i < c->num_chave)
        {
            if (chave >= c->chave[i])
            {
                i++;
            }
            else
            {
                break;
            }
        }

        if (verbose == 1)
        {
            printf("%d ->\n", i);
        }

        c = (Node *)c->ponteiro[i];
    }

    if (verbose == 1)
    {
        printf("Folha [");
        for (i = 0; i < c->num_chave - 1; i++)
        {
            printf("%d ", c->chave[i]);
        }
        printf("%d] ->\n", c->chave[i]);
    }

    return c;
}

Registro *encontrar(Node *raiz, int chave, int verbose, Node **fora_folha)
{

    if (raiz == NULL)
    {
        if (fora_folha != NULL)
        {
            *fora_folha = NULL;
        }
        return NULL;
    }

    int i = 0;
    Node *folha = NULL;

    folha = encontrarFolha(raiz, chave, verbose);

    for (i = 0; i < folha->num_chave; i++)
    {
        if (folha->chave[i] == chave)
        {
            break;
        }
    }

    if (fora_folha != NULL)
    {
        *fora_folha = folha;
    }

    if (i == folha->num_chave)
    {
        return NULL;
    }
    else
    {
        return (Registro *)folha->ponteiro[i];
    }
}

int cut(int length)
{

    if (length % 2 == 0)
    {
        return (length / 2);
    }
    else
    {
        return (length / 2 + 1);
    }
}

Registro *criarRegistro(int valor)
{
    Registro *novo_registro = (Registro *)malloc(sizeof(Registro));
    if (novo_registro == NULL)
    {
        perror("Record creation.");
        exit(EXIT_FAILURE);
    }
    else
    {
        novo_registro->valor = valor;
    }
    return novo_registro;
}

Node *criaNode(void)
{
    Node *novo_node;
    novo_node = malloc(sizeof(Node));
    if (novo_node == NULL)
    {
        perror("Node creation.");
        exit(EXIT_FAILURE);
    }
    novo_node->chave = malloc((ORDER - 1) * sizeof(int));
    if (novo_node->chave == NULL)
    {
        perror("New node keys array.");
        exit(EXIT_FAILURE);
    }
    novo_node->ponteiro = malloc(ORDER * sizeof(void *));
    if (novo_node->ponteiro == NULL)
    {
        perror("New node pointers array.");
        exit(EXIT_FAILURE);
    }
    novo_node->eh_folha = 0;
    novo_node->num_chave = 0;
    novo_node->pai = NULL;
    novo_node->prox = NULL;
    return novo_node;
}

Node *criaFolha(void)
{
    Node *folha = criaNode();
    folha->eh_folha = 1;
    return folha;
}

int getIndiceEsquerda(Node *pai, Node *esquerda)
{
    int indice_esquerda = 0;
    while (indice_esquerda <= pai->num_chave && pai->ponteiro[indice_esquerda] != esquerda)
        indice_esquerda++;
    return indice_esquerda;
}

Node *inserirFolha(Node *folha, int chave, Registro *ponteiro)
{
    int i, inserir_ponto;

    inserir_ponto = 0;
    while (inserir_ponto < folha->num_chave && folha->chave[inserir_ponto] < chave)
        inserir_ponto++;

    for (i = folha->num_chave; i > inserir_ponto; i--)
    {
        folha->chave[i] = folha->chave[i - 1];
        folha->ponteiro[i] = folha->ponteiro[i - 1];
    }
    folha->chave[inserir_ponto] = chave;
    folha->ponteiro[inserir_ponto] = ponteiro;
    folha->num_chave++;
    return folha;
}

Node *inserirFolhaAposDivisao(Node *raiz, Node *folha, int chave, Registro *ponteiro)
{

    Node *nova_folha;
    int *temp_chave;
    void **temp_ponteiros;
    int indice_insercao, dividir, nova_chave, i, j;

    nova_folha = criaFolha();

    temp_chave = malloc(ORDER * sizeof(int));

    if (temp_chave == NULL)
    {
        perror("Temporary keys array");
        exit(EXIT_FAILURE);
    }

    temp_ponteiros = malloc(ORDER * sizeof(void *));

    if (temp_ponteiros == NULL)
    {
        perror("Temporary pointers array.");
        exit(EXIT_FAILURE);
    }

    indice_insercao = 0;
    while (indice_insercao < ORDER - 1 && folha->chave[indice_insercao] < chave)
    {
        indice_insercao++;
    }

    for (i = 0, j = 0; i < folha->num_chave; i++, j++)
    {
        if (j == indice_insercao)
        {
            j++;
        }

        temp_chave[j] = folha->chave[i];
        temp_ponteiros[j] = folha->ponteiro[i];
    }

    temp_chave[indice_insercao] = chave;
    temp_ponteiros[indice_insercao] = ponteiro;

    folha->num_chave = 0;

    dividir = cut(ORDER - 1);

    for (i = 0; i < dividir; i++)
    {
        folha->ponteiro[i] = temp_ponteiros[i];
        folha->chave[i] = temp_chave[i];
        folha->num_chave++;
    }

    for (i = dividir, j = 0; i < ORDER; i++, j++)
    {
        nova_folha->ponteiro[j] = temp_ponteiros[i];
        nova_folha->chave[j] = temp_chave[i];
        nova_folha->num_chave++;
    }

    free(temp_ponteiros);
    free(temp_chave);

    nova_folha->ponteiro[ORDER - 1] = folha->ponteiro[ORDER - 1];
    folha->ponteiro[ORDER - 1] = nova_folha;

    for (i = folha->num_chave; i < ORDER - 1; i++)
    {
        folha->ponteiro[i] = NULL;
    }
    for (i = nova_folha->num_chave; i < ORDER - 1; i++)
    {
        nova_folha->ponteiro[i] = NULL;
    }

    nova_folha->pai = folha->pai;
    nova_chave = nova_folha->chave[0];

    return inserirPai(raiz, folha, nova_chave, nova_folha);
}

Node *inserirNode(Node *raiz, Node *pai, int indice_esquerda, int chave, Node *direita)
{

    int i;

    for (i = pai->num_chave; i > indice_esquerda; i--)
    {
        pai->ponteiro[i + 1] = pai->ponteiro[i];
        pai->chave[i] = pai->chave[i - 1];
    }

    pai->ponteiro[indice_esquerda + 1] = direita;
    pai->chave[indice_esquerda] = chave;
    pai->num_chave++;
    return raiz;
}

Node *inserirNodeAposDivisao(Node *raiz, Node *pai, int indice_esquerda, int chave, Node *direita)
{

    int i, j, dividir, k;
    Node *novo_node, *filho;
    int *temp_chave;
    Node **temp_ponteiro;

    temp_ponteiro = malloc((ORDER + 1) * sizeof(Node *));

    if (temp_ponteiro == NULL)
    {
        exit(EXIT_FAILURE);
    }

    temp_chave = malloc(ORDER * sizeof(int));

    if (temp_chave == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (i = 0, j = 0; i < pai->num_chave + 1; i++, j++)
    {
        if (j == indice_esquerda + 1)
        {
            j++;
        }
        temp_ponteiro[j] = pai->ponteiro[i];
    }

    for (i = 0, j = 0; i < pai->num_chave; i++, j++)
    {
        if (j == indice_esquerda)
        {
            j++;
        }

        temp_chave[j] = pai->chave[i];
    }

    temp_ponteiro[indice_esquerda + 1] = direita;
    temp_chave[indice_esquerda] = chave;

    dividir = cut(ORDER);
    novo_node = criaNode();
    pai->num_chave = 0;

    for (i = 0; i < dividir - 1; i++)
    {

        pai->ponteiro[i] = temp_ponteiro[i];
        pai->chave[i] = temp_chave[i];
        pai->num_chave++;
    }

    pai->ponteiro[i] = temp_ponteiro[i];
    k = temp_chave[dividir - 1];

    for (++i, j = 0; i < ORDER; i++, j++)
    {
        novo_node->ponteiro[j] = temp_ponteiro[i];
        novo_node->chave[j] = temp_chave[i];
        novo_node->num_chave++;
    }

    novo_node->ponteiro[j] = temp_ponteiro[i];

    free(temp_ponteiro);
    free(temp_chave);

    novo_node->pai = pai->pai;

    for (i = 0; i <= novo_node->num_chave; i++)
    {

        filho = novo_node->ponteiro[i];
        filho->pai = novo_node;
    }

    return inserirPai(raiz, pai, k, novo_node);
}

Node *inserirPai(Node *raiz, Node *esquerda, int chave, Node *direita)
{

    int indice_esquerda;
    Node *pai;

    pai = esquerda->pai;

    if (pai == NULL)
    {
        return inserirNovaRaiz(esquerda, chave, direita);
    }

    indice_esquerda = getIndiceEsquerda(pai, esquerda);

    if (pai->num_chave < ORDER - 1)
    {
        return inserirNode(raiz, pai, indice_esquerda, chave, direita);
    }

    return inserirNodeAposDivisao(raiz, pai, indice_esquerda, chave, direita);
}

Node *inserirNovaRaiz(Node *esquerda, int chave, Node *direita)
{

    Node *raiz = criaNode();
    raiz->chave[0] = chave;
    raiz->ponteiro[0] = esquerda;
    raiz->ponteiro[1] = direita;
    raiz->num_chave++;
    raiz->pai = NULL;
    esquerda->pai = raiz;
    direita->pai = raiz;
    return raiz;
}

Node *iniciarNovaArvore(int chave, Registro *ponteiro)
{

    Node *raiz = criaFolha();
    raiz->chave[0] = chave;
    raiz->ponteiro[0] = ponteiro;
    raiz->ponteiro[ORDER - 1] = NULL;
    raiz->pai = NULL;
    raiz->num_chave++;
    return raiz;
}

Node *inserir(Node *raiz, int chave, int valor)
{

    Registro *registo_ponteiro = NULL;
    Node *folha = NULL;

    registo_ponteiro = encontrar(raiz, chave, 0, NULL);
    if (registo_ponteiro != NULL)
    {
        registo_ponteiro->valor = valor;
        return raiz;
    }

    registo_ponteiro = criarRegistro(valor);

    if (raiz == NULL)
    {
        return iniciarNovaArvore(chave, registo_ponteiro);
    }

    folha = encontrarFolha(raiz, chave, 0);

    if (folha->num_chave < ORDER - 1)
    {
        folha = inserirFolha(folha, chave, registo_ponteiro);
        return raiz;
    }

    return inserirFolhaAposDivisao(raiz, folha, chave, registo_ponteiro);
}