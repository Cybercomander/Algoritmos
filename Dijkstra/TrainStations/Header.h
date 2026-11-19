#ifndef HEADER_H
#define HEADER_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <limits.h>

    #define MAX_NOMBRE 20
    #define INFINITO INT_MAX        //Distancia de un vértice aún no alcanzado

    // DEFINICIÓN DE ESTRUCTURAS
    typedef struct vertice Vertice;
    typedef struct arista Arista;
    typedef struct graph Graph;
    typedef struct stack Stack;
    typedef struct nodoHeap NodoHeap;
    typedef struct heap Heap;

    // Estructuras para grafos
    struct vertice{
        char nombre[MAX_NOMBRE];    //Nombre de la ciudad
        Arista * lista;             //Aristas que salen de este vértice (grafo dirigido)
        int nexo;                   //Cantidad de vecinos (aristas) de este vértice
        int distancia;              //Costo acumulado desde el origen (lo llena Dijkstra)
        Vertice * previo;           //Vértice anterior en el camino más corto
        int visitado;               //1 si Dijkstra ya fijó su distancia definitiva
    };

    struct arista{
        Vertice * destino;
        int peso;                   //Precio del trayecto en $
    };

    struct graph{
        Vertice * nodos;            //Vértice de inicio del recorrido
        int grado;                  //Cantidad de vértices
        Stack * vertices;           //Todos los vértices del grafo (incluye los no alcanzables desde nodos)
    };

    // Estructuras para Pilas (usada por el DFS y como registro de vértices)
    struct stack{
        Vertice ** datos;           //Arreglo dinámico de punteros a vértices
        int cant;                   //Elementos actuales
        int cap;                    //Capacidad reservada
    };

    // Estructuras para el Heap (min-heap por distancia)
    struct nodoHeap{
        Vertice * vertice;
        int distancia;              //Distancia con la que se insertó (puede quedar obsoleta)
    };

    struct heap{
        NodoHeap * datos;           //Arreglo dinámico que representa el árbol binario
        int cant;
        int cap;
    };

    /* PROTOTIPOS DE FUNCIONES */
    //Prototipos para el grafo
    Graph * Graph_init(void);
    void liberarGrafo(Graph * grafo);
    Vertice * crearVertice(Graph * grafo, const char * nombre);
    Vertice * buscarVertice(Graph * grafo, const char * nombre);
    int addArista(Graph * grafo, const char * origen, const char * destino, int peso);

    //Prototipos para la pila
    Stack * Stack_init(void);
    int Stack_void(Stack * pila);       //Devuelve 1 si la pila tiene elementos
    void push(Stack * pila, Vertice * vertice);
    Vertice * pop(Stack * pila);
    void Stack_free(Stack * pila);

    //Prototipos para el heap
    Heap * Heap_init(void);
    int Heap_void(Heap * heap);         //Devuelve 1 si el heap tiene elementos
    void Heap_push(Heap * heap, Vertice * vertice, int distancia);
    NodoHeap Heap_pop(Heap * heap);     //Extrae el nodo de menor distancia
    void Heap_free(Heap * heap);

    //Prototipos para el recorrido
    int visitado(Stack * visitados, Vertice * nodo);
    Vertice * dfs(Graph * grafo, Vertice * inicio, const char * nombre);

    //Prototipos para Dijkstra
    void dijkstra(Graph * grafo, Vertice * origen);
    void imprimirCamino(Vertice * destino);

#endif
