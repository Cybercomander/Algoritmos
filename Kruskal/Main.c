#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

int main(void) {
    int num_vertices = 5;
    Grafo *g = crear_grafo(num_vertices);

    agregar_arista(g, 0, 1, 2);
    agregar_arista(g, 1, 2, 3);
    agregar_arista(g, 1, 4, 5);
    agregar_arista(g, 0, 3, 6);
    agregar_arista(g, 2, 4, 7);
    agregar_arista(g, 1, 3, 8);
    agregar_arista(g, 3, 4, 9);

    int num_aristas, num_mst;
    Arista *aristas = extraer_aristas(g, &num_aristas);
    Arista *mst = malloc((num_vertices - 1) * sizeof(Arista));

    int peso = kruskal(aristas, num_aristas, g->num_vertices, mst, &num_mst);
    printf("%d\n", peso);

    free(mst);
    free(aristas);
    liberar_grafo(g);
    return 0;
}