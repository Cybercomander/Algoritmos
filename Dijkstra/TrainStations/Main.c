#include "Header.h"

// Ruta turística de Tokio: camino más barato de Minato a Koto usando Dijkstra.
int main(void){
    Graph * grafo = Graph_init();
    if(grafo == NULL)
        return 1;

    //Vértices: el primero (minato) queda como inicio del grafo
    const char * ciudades[] = {"minato", "shibuya", "shinjuku", "nakano",
                                "toshima", "taito", "bunkyo", "koto"};
    for(int i = 0; i < 8; i++)
        crearVertice(grafo, ciudades[i]);

    //Aristas dirigidas según las flechas de la imagen (peso = precio en $)
    addArista(grafo, "minato",   "shibuya",  22);
    addArista(grafo, "shibuya",  "shinjuku", 18);
    addArista(grafo, "shibuya",  "nakano",   30);
    addArista(grafo, "shinjuku", "minato",   26);
    addArista(grafo, "nakano",   "toshima",  24);
    addArista(grafo, "toshima",  "shinjuku", 20);
    addArista(grafo, "toshima",  "taito",    35);
    addArista(grafo, "taito",    "bunkyo",   15);
    addArista(grafo, "bunkyo",   "koto",     40);
    addArista(grafo, "koto",     "taito",    24);

    //DFS: confirma que koto es alcanzable desde minato antes de calcular
    Vertice * origen = grafo->nodos;
    Vertice * destino = dfs(grafo, origen, "koto");
    if(destino == NULL){
        printf("koto no es alcanzable desde %s\n", origen->nombre);
        liberarGrafo(grafo);
        return 1;
    }

    dijkstra(grafo, origen);
    imprimirCamino(destino);

    liberarGrafo(grafo);
    return 0;
}
