#include "arvoreb.h"

Arvoreb *cria_arvoreb(int ordem)
{
    Arvoreb *nova = (Arvoreb *)malloc(sizeof(Arvoreb));

    nova->raiz = NULL;
    nova->ordem = ordem;
    nova->altura = 0;
    return nova;
}

Nob *cria_nob()
{
    Nob *novo = (Nob *)malloc(sizeof(Nob)), novo2;

    novo->folha = 1;
    novo->pai = NULL;
    novo->qtd_chaves = 0;
    novo->lista_chaves = cria_listad();

    return novo;
}

Chave *cria_chave(int valor)
{
    Chave *ch = (Chave *)malloc(sizeof(Chave));
    ch->filho = NULL;
    ch->valor_chave = valor;
    return ch;
}

Listad *divide_lista(Listad *L, int n)
{
    Listad *L2 = cria_listad();
    Nod *aux = L->ini;
    while (n > 1)
    {
        aux = aux->prox;
        n--;
    }
    L2->fim = L->fim;
    L->fim = aux;
    L2->ini = aux->prox;
    L2->ini->ant = NULL;
    L->fim->prox = NULL;
    return L2;
}

Listad *insere_ordenado_listad(Listad *lista_nos,
                               Chave *chave_nova)
{

    Nod *aux = lista_nos->ini;
    void *ch;

    while (aux->prox != NULL && chave_nova->valor_chave > get_valor_chave(aux))
    {
        aux = aux->prox;
    }
    if (aux == lista_nos->ini)
    {
        lista_nos = insere_inicio_listad(lista_nos, (void *)chave_nova);
    }
    else
    {
        if (aux == NULL)
        {
            ch = remove_fim_listad(lista_nos);
            lista_nos = insere_fim_listad(lista_nos, (void *)chave_nova);
            lista_nos = insere_fim_listad(lista_nos, ch);
        }
        else
        {
            Nod *novo = cria_nod((void *)chave_nova);
            novo->prox = aux;
            novo->ant = aux->ant;
            aux->ant->prox = novo;
            aux->ant = novo;
        }
    }
    return lista_nos;
}

int get_valor_chave(Nod *aux)
{
    return ((Chave *)aux->info)->valor_chave;
}

Nob *get_filho(Nod *aux)
{
    return ((Chave *)aux->info)->filho;
}

void set_filho(Nod *aux, Nob *novo_filho)
{
    ((Chave *)aux->info)->filho = novo_filho;
}

/*
inicio
  encontre uma folha para inserir a chave  K
  enquanto tem valor para inserir
  insira K na folha encontrada (insere ordenado na lista)
  se (nó não está cheio) entao
         marque que não tem mais valor para inserir
  senão
        divida o nó em nó1 e nó2; //nó1 == nó, nó2 eh novo
     K = ultima chave de nó1; //a qual é retirada de nó1
        se (nó era a raiz) entao
            crie uma nova raiz como ascendente de nó1 e nó2;
            coloque K e ponteiros para nó1 e nó2 na raiz e
            marque que não tem mais valor para inserir
        senao
            folha = seu pai;
        fimse
  fimse
  fimenquanto
fim
*/

void insercao_arvoreb(Arvoreb *tree, int chave)
{

    Chave *ch = cria_chave(chave);
    Nob *folha = localiza_folha(tree, chave);
    int tem_valor = 1;
    Nob *novo = NULL;
    if (tree->raiz == NULL)
    {
        tree->raiz = cria_nob();
        tree->raiz->lista_chaves = insere_primeira_chave(tree->raiz->lista_chaves, (void *)ch);
        tree->raiz->qtd_chaves++;
    }
    else
    {
        while (tem_valor)
        {
            folha->lista_chaves = insere_ordenado_listad(folha->lista_chaves, ch);
            folha->qtd_chaves++;
            if (folha->qtd_chaves < tree->ordem)
            {
                tem_valor = 0;
            }
            else
            {
                novo = divide_no(folha);
                ch = remove_ultima_chave(folha);
                if (folha == tree->raiz)
                {
                    tree->raiz = cria_nova_raiz(ch, folha, novo);
                    tem_valor = 0;
                }
                else
                {
                    folha = folha->pai;
                }
            }
        }
    }
}

Chave *remove_ultima_chave(Nob *folha)
{
    void *ch = remove_fim_listad(folha->lista_chaves);
    Chave *ult = (Chave *)remove_fim_listad(folha->lista_chaves);
    folha->lista_chaves = insere_fim_listad(folha->lista_chaves, ch);
    return ult;
}

Listad *insere_primeira_chave(Listad *L, void *ch)
{
    L = insere_inicio_listad(L, ch);
    L = insere_fim_listad(L, (void *)cria_chave(-1));
    return L;
}

Nob *localiza_folha(Arvoreb *tree, int chave)
{
    Nob *aux = tree->raiz;

    while (aux != NULL && aux->folha == 0) // nao for folha
    {
        Nod *aux_lista = aux->lista_chaves->ini;
        while (aux_lista->prox != NULL &&
               chave > get_valor_chave(aux_lista)) // para em cima do -1
        {
            aux_lista = aux_lista->prox;
        }
        aux = get_filho(aux_lista); //((Chave*)aux_lista->info)->filho;
    }
    return aux;
}
Chave *get_ultima_chave(Nob *aux)
{
    return ((Chave *)aux->lista_chaves->fim->ant->info);
}
Nob *divide_no(Nob *no_dividir)
{
    Chave *ch_subir;
    Nod *aux;
    Nob *novo = cria_nob();
    int n = ceil(no_dividir->qtd_chaves / 2.0);
    /*
    if (no_dividir->qtd_chaves % 2 != 0)
       n = no_dividir->qtd_chaves/2 + 1;
    else
       n = no_dividir->qtd_chaves/2;
    */
    novo->lista_chaves = divide_lista(
        no_dividir->lista_chaves, n);
    // colocar -1 no final do nó que dividiu
    no_dividir->lista_chaves = insere_fim_listad(
        no_dividir->lista_chaves, (void *)cria_chave(-1));
    no_dividir->qtd_chaves = n;

    novo->folha = no_dividir->folha;
    novo->qtd_chaves = no_dividir->qtd_chaves - n;
    novo->pai = no_dividir->pai;

    if (no_dividir->folha != 0) // for folha
    {
        ch_subir = get_ultima_chave(no_dividir);
        ch_subir->filho = no_dividir;

        // localiza o apontador do no_dividir
        if (no_dividir->pai != NULL)
        {
            aux = no_dividir->pai->lista_chaves->ini;

            while (get_filho(aux) != no_dividir)
                aux = aux->prox;

            set_filho(aux, novo);
        }
    }
    else
    {
        aux = novo->lista_chaves->ini;
        while (aux->prox != NULL)
        {
            get_filho(aux)->pai = novo;
            aux = aux->prox;
        }
        set_filho(aux, novo);
    }

    return novo;
}

Nob *cria_nova_raiz(Chave *chave_a_subir, Nob *no_insercao, Nob *novo)
{
    Nob *nova_raiz = cria_nob();

    nova_raiz->folha = 0;
    nova_raiz->lista_chaves = insere_primeira_chave(nova_raiz->lista_chaves, chave_a_subir);
    nova_raiz->pai = NULL;
    nova_raiz->qtd_chaves = 1;
    set_filho(nova_raiz->lista_chaves->fim, novo);
    chave_a_subir->filho = no_insercao;
    novo->pai = nova_raiz;
    no_insercao->pai = nova_raiz;
    return nova_raiz;
}

Nob *libera_nob(Nob *raiz)
{
    Nod *aux;
    if (raiz != NULL)
    {
        aux = raiz->lista_chaves->ini;
        while (aux != NULL)
        {
            ((Chave *)aux->info)->filho = libera_nob(((Chave *)aux->info)->filho);
            aux = aux->prox;
        }

        free(raiz);
    }
    return NULL;
}

Arvoreb *libera_arvoreb(Arvoreb *T)
{
    T->raiz = libera_nob(T->raiz);
    free(T);
    return NULL;
}

void mostra_nob(Nob *raiz, int detalhe)
{
    Listad *l = raiz->lista_chaves;
    Nod *aux = l->ini;

    if (detalhe)
    {

        // pai
        if (raiz->pai == NULL)
            printf("pai: nulo-");
        else
            printf("pai:%d-", ((Chave *)raiz->pai->lista_chaves->ini->info)->valor_chave);

        // se é folha
        printf("(%d)Folha:%d ", raiz->qtd_chaves, raiz->folha);
        // qtde de chaves
    }
    // valores
    printf("[");
    while (aux != NULL)
    {
        // filho
        //   printf("-%p ",((Chave*)aux->info)->filho);

        printf("%d ", ((Chave *)aux->info)->valor_chave);

        aux = aux->prox;
    }
    printf("]");
}

void em_ordem(Nob *raiz)
{
    Nod *aux;
    if (raiz != NULL)
    {
        aux = raiz->lista_chaves->ini;
        while (aux != NULL)
        {
            em_ordem(get_filho(aux));
            printf("%d ", get_valor_chave(aux));
            aux = aux->prox;
        }
    }
}

void percurso_em_nivel_posicionado(Arvoreb *T)
{
    int largura = 250;//pow(2, T->altura)*T->ordem*2;
    Fila *f = cria_fila();
    enqueue(f, (void*)T->raiz);

    em_nivel_posicionado(f,0, largura);
}

void em_nivel_posicionado(Fila *f, int nivel, int largura_tela)
{
    Fila *f_nova = cria_fila();
    Nob *auxb=NULL;
    Nod *aux=NULL;
    int nro_elementos = pow(2, nivel);
    int intervalo = largura_tela /(nro_elementos+1);
    int x = 3;
    while (eh_vazia_fila(f) != 1)
    {
        auxb = (Nob*)dequeue(f);

        gotoxy(intervalo+x, nivel+1);
        mostra_nob(auxb,1);

      //  if (auxb != NULL)
        {
            aux = auxb->lista_chaves->ini;
            while(aux != NULL)
            {
                if (((Chave*)aux->info)->filho != NULL)
                    enqueue(f_nova, (void*)((Chave*)aux->info)->filho);
                aux=aux->prox;
            }
        }
        x = x+intervalo;
    }
    printf ("\n");
    if(!eh_vazia_fila(f_nova))
        em_nivel_posicionado(f_nova, nivel+1,largura_tela);
}

// Função gotoxy
void gotoxy(int x, int y)
{
    COORD coord;

    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}