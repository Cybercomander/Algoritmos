#include <stdio.h>
#include "dijkstra.h"

/* Vertices: A=0, B=1, C=2, D=3, E=4, F=5, G=6 */
enum { A, B, C, D, E, F, G };

int main(void) {
    int origen, destino;
    int d[7], pred[7];   /* tamano del grafo mas grande (7 vertices) */

    /* ---------- Grafo no dirigido (6 vertices) ---------- */
    Grafo *g1 = crear_grafo(6, false);
    agregar_arista(g1, A, B, 4);
    agregar_arista(g1, A, C, 2);
    agregar_arista(g1, B, C, 1);
    agregar_arista(g1, B, D, 5);
    agregar_arista(g1, C, D, 8);
    agregar_arista(g1, C, E, 10);
    agregar_arista(g1, D, E, 2);
    agregar_arista(g1, D, F, 6);
    agregar_arista(g1, E, F, 3);

    printf("=== Grafo no dirigido ===\n");
    imprimir_grafo(g1);

    origen = A;
    destino = F;
    dijkstra(g1, origen, d, pred);
    printf("\nDistancia mas corta %c -> %c: ", 'A' + origen, 'A' + destino);
    if (d[destino] == INF) {
        printf("no alcanzable\n");
    } else {
        printf("%d   camino: ", d[destino]);
        imprimir_camino(pred, destino);
        printf("\n");
    }
    liberar_grafo(g1);

    /* ---------- Grafo dirigido (7 vertices) ---------- */
    Grafo *g2 = crear_grafo(7, true);
    agregar_arista(g2, A, B, 6);
    agregar_arista(g2, A, C, 2);
    agregar_arista(g2, C, B, 3);
    agregar_arista(g2, C, D, 7);
    agregar_arista(g2, C, E, 4);
    agregar_arista(g2, B, D, 2);
    agregar_arista(g2, D, B, 1);
    agregar_arista(g2, D, F, 3);
    agregar_arista(g2, E, D, 1);
    agregar_arista(g2, E, F, 6);
    agregar_arista(g2, F, E, 2);
    agregar_arista(g2, G, F, 1);

    printf("\n=== Grafo dirigido ===\n");
    imprimir_grafo(g2);

    origen = A;
    destino = F;
    dijkstra(g2, origen, d, pred);
    printf("\nDistancia mas corta %c -> %c: ", 'A' + origen, 'A' + destino);
    if (d[destino] == INF) {
        printf("no alcanzable\n");
    } else {
        printf("%d   camino: ", d[destino]);
        imprimir_camino(pred, destino);
        printf("\n");
    }
    liberar_grafo(g2);

    return 0;
}
