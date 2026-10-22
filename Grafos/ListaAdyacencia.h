#ifndef LISTA_H
#define LISTA_H

#include "Estructuras.h"

// FUNCION PARA GENERAR LA LISTA DE ADYACENCIA (UNA LISTA LIGADA POR VERTICE)
Elemento **generar_lista(Grafo *g);
// FUNCION PARA IMPRIMIR LA LISTA DE ADYACENCIA
void imprimir_lista(Grafo *g, Elemento **l);
// FUNCION PARA LIBERAR LA LISTA DE ADYACENCIA
void liberar_lista(Elemento **l, int n);

#endif
