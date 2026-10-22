#ifndef HEADER_H
#define HEADER_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include "Estructuras.h"
    #include "MatrizAdyacencia.h"
    #include "ListaAdyacencia.h"

// FUNCION PARA CREAR UN NUEVO NODO EN EL GRAFO
Nodo *crear_nodo(int dato);
// FUNCION PARA CREAR EL GRAFO CON SU PRIMER VERTICE
Grafo *crear_grafo(int dato);
// FUNCION PARA BUSCAR EL INDICE DE UN VERTICE POR SU DATO (-1 SI NO EXISTE)
int buscar_vertice(Grafo *g, int dato);
// FUNCION PARA AGREGAR UN VERTICE AL GRAFO (REALLOC DEL ARREGLO)
Nodo *insertarNodo(Grafo *g, int dato);
// FUNCION PARA AGREGAR UNA ARISTA NO DIRIGIDA ENTRE DOS VERTICES
int agregar_arista(Nodo *a, Nodo *b);
//FUNCIÓN PARA LIBERAR LA MEMORIA DEL GRAFO
void liberar_memoria(Grafo *g);

#endif
