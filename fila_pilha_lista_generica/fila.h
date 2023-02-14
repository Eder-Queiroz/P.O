#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include "listadupla.h"

typedef Listad Fila;

Fila* cria_fila();

Fila* enqueue(Fila *f, void* elemento);
void* dequeue(Fila *f);
int eh_vazia_fila(Fila *f);

#endif // FILA_H_INCLUDED
