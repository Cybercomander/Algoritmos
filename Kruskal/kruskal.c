#include "kruskal.h"
#include <stdlib.h>

// grafo
Grafo *crear_grafo(int num_vertices) {
    Grafo *g = malloc(sizeof(Grafo));                   
    if (g == NULL)
        return NULL;
    g->num_vertices = num_vertices;
    g->lista = calloc(num_vertices, sizeof(Nodo*));
    return g;
}

void agregar_arista(Grafo *g, int u, int v, int peso) {
    Nodo *a = malloc(sizeof(Nodo));
    a->destino = v;
    a->peso = peso;
    a->siguiente = g->lista[u];
    g->lista[u] = a;

    Nodo *b = malloc(sizeof(Nodo));
    b->destino = u;
    b->peso = peso;
    b->siguiente = g->lista[v];
    g->lista[v] = b;
}

Arista *extraer_aristas(Grafo *g, int *m) {
    int total = 0;
    for (int u = 0; u < g->num_vertices; u++) {
        for (Nodo *p = g->lista[u]; p != NULL; p = p->siguiente) {
            if (u < p->destino)
                total++;
        }
    }
    int k = 0;
    Arista *aristas = malloc(total * sizeof(Arista));
    for (int u = 0; u < g->num_vertices; u++) {
        for (Nodo *p = g->lista[u]; p != NULL; p = p->siguiente) {
            if (u < p->destino) {
                aristas[k++] = (Arista){u, p->destino, p->peso};
            }
        }
    }
    *m = total;
    return aristas;
}

void liberar_grafo(Grafo *g) {
    for (int u = 0; u < g->num_vertices; u++) {
        Nodo *p = g->lista[u];
        while (p != NULL) {
            Nodo *t = p->siguiente;
            free(p);
            p = t;
        }
    }
    free(g->lista);
    free(g);
}

// unionfind
UnionFind *crear_union_find(int num_vertices) {
    UnionFind *s = malloc(sizeof(UnionFind));
    s->raiz = malloc(num_vertices * sizeof(int));
    s->rango = malloc(num_vertices * sizeof(int));
    for (int i = 0; i < num_vertices; i++) {
        s->raiz[i] = i;
        s->rango[i] = 0;
    }
    return s;
}

int find_raiz(UnionFind *s, int id) {
    while (s->raiz[id] != id) {
        s->raiz[id] = s->raiz[s->raiz[id]];
        id = s->raiz[id];
    }
    return id;
}

bool unir(UnionFind *s, int u, int v) {
    int raiz_u = find_raiz(s, u);
    int raiz_v = find_raiz(s, v);

    if (raiz_u == raiz_v)
        return false;

    if (s->rango[raiz_u] < s->rango[raiz_v]) {
        s->raiz[raiz_u] = raiz_v;
    } else if (s->rango[raiz_u] > s->rango[raiz_v]) {
        s->raiz[raiz_v] = raiz_u;
    } else {
        s->raiz[raiz_v] = raiz_u;
        s->rango[raiz_u]++;
    }
    return true;
}

void liberar_union_find(UnionFind *s) {
    free(s->raiz);
    free(s->rango);
    free(s);
}

// sort
void swap(Arista *a, Arista *b) {
    Arista temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(Arista *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j].peso > arr[j+1].peso) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

// kruskal
int kruskal(Arista *aristas, int num_aristas, int num_vertices,  Arista *mst, int *num_mst) {
    bubble_sort(aristas, num_aristas);

    UnionFind *s = crear_union_find(num_vertices);
    int peso_total = 0;
    *num_mst = 0;

    for (int i = 0; i < num_aristas; i++) {
        if (unir(s, aristas[i].u, aristas[i].v)) {
            mst[(*num_mst)++] = aristas[i];
            peso_total += aristas[i].peso;

            if (*num_mst == num_vertices - 1)
                break;
        }
    }

    liberar_union_find(s);
    return peso_total;
}