#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <stdbool.h>

typedef struct {
    int u, v, peso;
} Arista;

typedef struct Nodo {
    int destino, peso;
    struct Nodo *siguiente;
} Nodo;

typedef struct {
    int num_vertices;
    Nodo **lista;
} Grafo;

typedef struct {
    int *raiz;
    int *rango;
} UnionFind;

// grafo
Grafo *crear_grafo(int num_vertices);
void agregar_arista(Grafo *g, int u, int v, int peso);
Arista *extraer_aristas(Grafo *g, int *m);
void liberar_grafo(Grafo *g);

// unionfind
UnionFind *crear_union_find(int num_vertices);
int find_raiz(UnionFind *s, int id);
bool unir(UnionFind *s, int u, int v);
void liberar_union_find(UnionFind *s);

// sort
void swap(Arista *a, Arista *b);
void bubble_sort(Arista *arr, int n);

// kruskal
int kruskal(Arista *aristas, int num_aristas, int num_vertices,  Arista *mst, int *num_mst);

#endif