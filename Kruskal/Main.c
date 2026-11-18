#include "Header.h"

// Uso: ./kruskal [archivo] [vértice_a_buscar]
// Sin argumentos lee Grafo1.txt (desde la carpeta Kruskal).
int main(int argc, char * argv[]){
    const char * ruta = argc > 1 ? argv[1] : "Grafo1.txt";
    int dirigido = 0;

    Graph * grafo = leerGrafo(ruta, &dirigido);
    if(grafo == NULL)
        return 1;

    printf("Grafo %s con %d vértices\n", dirigido ? "dirigido" : "no dirigido", grafo->grado);

    if(argc > 2){
        int buscado = atoi(argv[2]);
        printf(dfs(grafo, buscado) ? "\nEl vértice %d es alcanzable desde el inicio (%d)\n"
                                : "\nEl vértice %d no es alcanzable desde el inicio (%d)\n",
                buscado, grafo->nodos->dato);
    }

    int cant = 0;
    Arco * mst = kruskal(grafo, &cant);
    int total = 0;

    printf("\nÁrbol de expansión mínimo (%d aristas):\n", cant);
    for(int i = 0; i < cant; i++){
        printf("  %d - %d  peso %d\n", mst[i].origen->dato, mst[i].destino->dato, mst[i].peso);
        total += mst[i].peso;
    }
    printf("Peso total: %d\n", total);

    free(mst);
    liberarGrafo(grafo);
    return 0;
}
