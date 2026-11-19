#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

/* ================= Lista de adyacencia ================= */

Grafo *crear_grafo(int num_vertices, bool es_dirigido) {
    Grafo *g = malloc(sizeof(Grafo));
    if (!g) return NULL;
    g->num_vertices = num_vertices;
    g->num_aristas = 0;
    g->es_dirigido = es_dirigido;
    g->lista = calloc(num_vertices, sizeof(Nodo *));   /* todo en NULL */
    if (!g->lista) { 
        free(g); return NULL;
    }
    return g;
}

/* Agrega UNA arista dirigida u -> v (insercion al inicio de la lista de u). */
static void agregar_dirigida(Grafo *g, int u, int v, int peso) {
    Nodo *n = malloc(sizeof(Nodo));
    if (!n) { fprintf(stderr, "Sin memoria\n"); exit(1); }
    n->destino = v;
    n->peso = peso;
    n->siguiente = g->lista[u];
    g->lista[u] = n;
    g->num_aristas++;
}

void agregar_arista(Grafo *g, int u, int v, int peso) {
    agregar_dirigida(g, u, v, peso);
    if (!g->es_dirigido)
        agregar_dirigida(g, v, u, peso);
}

void imprimir_grafo(const Grafo *g) {
    for (int u = 0; u < g->num_vertices; u++) {
        printf("%c:", 'A' + u);
        for (Nodo *p = g->lista[u]; p != NULL; p = p->siguiente)
            printf(" -> (%c, %d)", 'A' + p->destino, p->peso);
        printf(" -> NULL\n");
    }
}

void liberar_grafo(Grafo *g) {
    if (!g) return;
    for (int u = 0; u < g->num_vertices; u++) {
        Nodo *p = g->lista[u];
        while (p) {
            Nodo *sig = p->siguiente;
            free(p);
            p = sig;
        }
    }
    free(g->lista);
    free(g);
}

/* ================= Heap minimo ================= */

/* Orden: primero por distancia, en empate por numero de vertice. */
static bool menor(ElemHeap a, ElemHeap b) {
    if (a.distancia != b.distancia) return a.distancia < b.distancia;
    return a.vertice < b.vertice;
}

static void intercambiar(ElemHeap *a, ElemHeap *b) {
    ElemHeap t = *a; *a = *b; *b = t;
}

Heap *crear_heap(int capacidad) {
    Heap *h = malloc(sizeof(Heap));
    if (!h) return NULL;
    h->datos = malloc(capacidad * sizeof(ElemHeap));
    if (!h->datos) { free(h); return NULL; }
    h->tamano = 0;
    h->capacidad = capacidad;
    return h;
}

bool heap_vacio(const Heap *h) {
    return h->tamano == 0;
}

void heap_insertar(Heap *h, int distancia, int vertice) {
    if (h->tamano == h->capacidad) {
        fprintf(stderr, "Heap lleno\n");
        exit(1);
    }
    int i = h->tamano++;
    h->datos[i].distancia = distancia;
    h->datos[i].vertice = vertice;

    /* subir mientras sea menor que su padre */
    while (i > 0) {
        int padre = (i - 1) / 2;
        if (!menor(h->datos[i], h->datos[padre])) break;
        intercambiar(&h->datos[i], &h->datos[padre]);
        i = padre;
    }
}

ElemHeap heap_extraer_min(Heap *h) {
    ElemHeap min = h->datos[0];
    h->datos[0] = h->datos[--h->tamano];

    /* bajar la raiz a su lugar */
    int i = 0;
    while (true) {
        int izq = 2 * i + 1, der = 2 * i + 2, m = i;
        if (izq < h->tamano && menor(h->datos[izq], h->datos[m])) m = izq;
        if (der < h->tamano && menor(h->datos[der], h->datos[m])) m = der;
        if (m == i) break;
        intercambiar(&h->datos[i], &h->datos[m]);
        i = m;
    }
    return min;
}

void liberar_heap(Heap *h) {
    if (!h) return;
    free(h->datos);
    free(h);
}

/* ================= Dijkstra (version perezosa) ================= */

void dijkstra(const Grafo *g, int origen, int d[], int pred[]) {
    int V = g->num_vertices;
    bool *fijo = calloc(V, sizeof(bool));
    Heap *heap = crear_heap(g->num_aristas + 1);   /* una insercion por arista + la inicial */
    if (!fijo || !heap) { fprintf(stderr, "Sin memoria\n"); exit(1); }

    for (int v = 0; v < V; v++) {
        d[v] = INF;
        pred[v] = -1;
    }
    d[origen] = 0;
    heap_insertar(heap, 0, origen);

    while (!heap_vacio(heap)) {
        ElemHeap e = heap_extraer_min(heap);
        int u = e.vertice, du = e.distancia;

        if (fijo[u]) continue;          /* pareja obsoleta: se descarta */
        fijo[u] = true;

        for (Nodo *p = g->lista[u]; p != NULL; p = p->siguiente) {
            int v = p->destino;
            if (!fijo[v] && du + p->peso < d[v]) {   /* du es finito: no desborda */
                d[v] = du + p->peso;
                pred[v] = u;
                heap_insertar(heap, d[v], v);        /* la vieja se queda */
            }
        }
    }

    liberar_heap(heap);
    free(fijo);
}

void imprimir_camino(const int pred[], int destino) {
    if (pred[destino] != -1) {
        imprimir_camino(pred, pred[destino]);
        printf(" -> ");
    }
    printf("%c", 'A' + destino);
}
