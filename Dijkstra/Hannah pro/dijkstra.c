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
    if (a.distancia != b.distancia) 
        return a.distancia < b.distancia;
    return a.vertice < b.vertice;
}

static void intercambiar(ElemHeap *a, ElemHeap *b) {
    ElemHeap t = *a; 
    *a = *b; 
    *b = t;
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
    int i = 0;                                   /* empezamos en la raiz */
    while (true) {
        /* posiciones de los hijos; m guarda al mas pequeno de los tres */
        int izq = 2 * i + 1;
        int der = 2 * i + 2;
        int m = i;
        if (izq < h->tamano && menor(h->datos[izq], h->datos[m]))
            m = izq;                             /* el hijo izquierdo es menor */
        if (der < h->tamano && menor(h->datos[der], h->datos[m]))
            m = der;                             /* el hijo derecho es aun menor */
        if (m == i)
            break;                               /* ya es menor que sus hijos: esta en su lugar */
        intercambiar(&h->datos[i], &h->datos[m]); /* bajarlo un nivel */
        i = m;                                   /* seguir desde su nueva posicion */
    }
    return min;                                  /* devolver el minimo que estaba en la raiz */
}

void liberar_heap(Heap *h) {
    if (!h) return;
    free(h->datos);
    free(h);
}

/* ================= Dijkstra (version perezosa) ================= */

/* Calcula la distancia mas corta desde 'origen' a todos los vertices.
   Al terminar: d[v] = distancia minima a v, pred[v] = vertice anterior a v en ese camino. */
void dijkstra(const Grafo *g, int origen, int d[], int pred[]) {
    /* cuantos vertices tiene el grafo */
    int vertices = g->num_vertices;
    /* fijo[v] = true cuando ya conocemos la distancia final de v (empieza todo en false) */
    bool *fijo = calloc(vertices, sizeof(bool));
    /* cola de prioridad: siempre nos da el vertice con menor distancia.
       Tamano: una insercion por arista + la del origen */
    Heap *heap = crear_heap(g->num_aristas + 1);
    /* si no hubo memoria para alguno de los dos, avisar y terminar */
    if (!fijo || !heap) { fprintf(stderr, "Sin memoria\n"); exit(1); }

    /* al inicio no sabemos llegar a ningun vertice */
    for (int v = 0; v < vertices; v++) {
        d[v] = INF;      /* distancia "infinita": todavia no hay camino */
        pred[v] = -1;    /* -1: no tiene vertice anterior */
    }
    /* al origen se llega sin costo */
    d[origen] = 0;
    /* metemos el origen a la cola para empezar desde ahi */
    heap_insertar(heap, 0, origen);

    /* repetir mientras queden vertices por revisar */
    while (!heap_vacio(heap)) {
        /* sacar el vertice con la menor distancia */
        ElemHeap e = heap_extraer_min(heap);
        /* u = ese vertice, du = su distancia desde el origen */
        int u = e.vertice, du = e.distancia;

        /* si u ya estaba fijo, esta entrada es vieja: la ignoramos */
        if (fijo[u]) continue;
        /* la distancia de u ya es la definitiva */
        fijo[u] = true;

        /* recorrer cada vecino de u */
        for (Nodo *p = g->lista[u]; p != NULL; p = p->siguiente) {
            /* v = el vecino al que lleva esta arista */
            int v = p->destino;
            /* si v no esta fijo y pasar por u es mas corto que lo que ya teniamos...
               (du nunca es INF aqui, asi que la suma no se desborda) */
            if (!fijo[v] && du + p->peso < d[v]) {
                /* ...guardar la nueva distancia mas corta */
                d[v] = du + p->peso;
                /* recordar que a v se llega desde u */
                pred[v] = u;
                /* meter v a la cola con su nueva distancia
                   (la entrada vieja de v se queda; se ignora al salir) */
                heap_insertar(heap, d[v], v);
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
