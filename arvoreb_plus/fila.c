#include "fila.h"

Fila* cria_fila()
{
    return cria_listad();
}

Fila* enqueue(Fila *f, void* elemento)
{
    return insere_fim_listad(f, elemento);
}

void* dequeue(Fila *f)
{
    return remove_inicio_listad(f);
}

int eh_vazia_fila(Fila *f)
{
    return eh_vazia_listad(f);
}
