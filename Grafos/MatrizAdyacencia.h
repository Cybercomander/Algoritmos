#ifndef MATRIZ_H
#define MATRIZ_H

#include "Estructuras.h"

// FUNCION PARA GENERAR LA MATRIZ DE ADYACENCIA (n x n) DEL GRAFO
int **generar_matriz(Grafo *g);
// FUNCION PARA IMPRIMIR LA MATRIZ DE ADYACENCIA
void imprimir_matriz(Grafo *g, int **m);
// FUNCION PARA LIBERAR LA MATRIZ DE ADYACENCIA
void liberar_matriz(int **m, int n);

#endif
