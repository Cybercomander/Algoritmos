#include "Header.h"

Graph * Graph_init(void){
    Graph * grafo = (Graph*)calloc(1, sizeof(Graph));
    if(grafo == NULL)
        printf("\n No se pudo generar el grafo");

    grafo->grado = 0;
    grafo->nodos = NULL;
    grafo->vertices = Stack_init();

    return grafo;
}

//Libera el grafo: las listas de aristas, los vértices (registrados en grafo->vertices) y el grafo
void liberarGrafo(Graph * grafo){
    if(grafo == NULL)
        return;
    if(grafo->vertices != NULL){
        for(int i = 0; i < grafo->vertices->cant; i++){
            free(grafo->vertices->datos[i]->lista);
            free(grafo->vertices->datos[i]);
        }
    }
    Stack_free(grafo->vertices);
    free(grafo);
}

Vertice * crearVertice(int dato){
    // Crear un vértice en el heap
    Vertice * vertice = (Vertice *)calloc(1, sizeof(Vertice));
    if (vertice == NULL)
        printf("\n No se pudo generar un vértice");

    vertice->dato = dato;
    vertice->lista = NULL;
    vertice->nexo = 0;

    return vertice;
}

int addVertice(Graph * grafo, Vertice * origen, int dato, int peso){
    Vertice * v = dfs(grafo, origen->dato);   // vértice real dentro del grafo
    if(v == NULL){
        printf("\n No se encontró el vértice origen");
        return 0;
    }

    Arista * tmp = realloc(v->lista, (v->nexo + 1) * sizeof(Arista));
    if(tmp==NULL){
        printf("\n No se pudo realloc en lista");
        return 0;
    }

    v->lista = tmp;

    Vertice * nuevo = crearVertice(dato);
    v->lista[v->nexo].destino = nuevo;
    push(grafo->vertices, nuevo);       //Registrar el vértice en el grafo
    v->lista[v->nexo].peso = peso;
    v->nexo++;

    printf("\n Se agregó el vértice satisfactoriamente");
    return 1;
}
