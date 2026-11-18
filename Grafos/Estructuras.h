#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

// VERTICE DEL GRAFO: GUARDA SU DATO Y UN ARREGLO DINAMICO DE VECINOS
typedef struct nodo{
    struct nodo **adyacentes;   // VERTICES CON LOS QUE COMPARTE ARISTA
    int grado;                  // NUMERO DE ARISTAS DEL VERTICE
    int dato;
}Nodo;

// GRAFO NO DIRIGIDO: ARREGLO DINAMICO DE VERTICES (CRECE CON REALLOC)
typedef struct grafo{
    Nodo **vertices;
    int n;                      // NUMERO DE VERTICES
}Grafo;

// ELEMENTO DE LA LISTA DE ADYACENCIA (LISTA LIGADA SIMPLE)
typedef struct elemento{
    struct elemento *next;
    int dato;
}Elemento;

#endif
