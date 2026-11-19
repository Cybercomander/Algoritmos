#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdbool.h>
#include <limits.h>

#define INF INT_MAX

/* ---------- Lista de adyacencia ---------- */

typedef struct Nodo {
    int destino, peso;
    struct Nodo *siguiente;
} Nodo;

typedef struct {
    int num_vertices;
    int num_aristas;      /* aristas dirigidas guardadas (para dimensionar el heap) */
    bool es_dirigido;
    Nodo **lista;         /* arreglo de num_vertices punteros a Nodo */
} Grafo;

Grafo *crear_grafo(int num_vertices, bool es_dirigido);
void   agregar_arista(Grafo *g, int u, int v, int peso);
void   imprimir_grafo(const Grafo *g);
void   liberar_grafo(Grafo *g);

/* ---------- Heap minimo de parejas (distancia, vertice) ---------- */

typedef struct {
    int distancia;
    int vertice;
} ElemHeap;

typedef struct {
    ElemHeap *datos;
    int tamano;
    int capacidad;
} Heap;

Heap *crear_heap(int capacidad);
void  heap_insertar(Heap *h, int distancia, int vertice);
ElemHeap heap_extraer_min(Heap *h);
bool  heap_vacio(const Heap *h);
void  liberar_heap(Heap *h);

/* ---------- Dijkstra ---------- */

/* Llena d[] y pred[] (ambos de tamano num_vertices, reservados por quien llama). */
void dijkstra(const Grafo *g, int origen, int d[], int pred[]);

/* Imprime el camino origen -> destino usando pred[] (recursivo). */
void imprimir_camino(const int pred[], int destino);

#endif
