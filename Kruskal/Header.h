#ifndef HEADER_H
#define HEADER_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

    /*DEFINICIÓN DE ESTRUCTURAS*/
    typedef struct vertice Vertice;
    typedef struct arista Arista;
    typedef struct graph Graph;
    typedef struct stack Stack;
    typedef struct arco Arco;

    // Estructuras para grafos
    struct vertice{
        int dato;
        Arista * lista;
        int nexo;               //Cantidad de vecinos (aristas) de este vértice
    };

    struct arista{
        Vertice * destino;
        int peso;
    };

    // Arista suelta, usada por el MST
    struct arco{
        Vertice * origen;
        Vertice * destino;
        int peso;
    };

    struct graph{
        Vertice * nodos;        //Vértice de inicio del recorrido
        int grado;
        Stack * vertices;       //Todos los vértices del grafo (incluye los no alcanzables desde nodos)
    };

    // Estructuras para Pilas
    struct stack{
        Vertice ** datos;       //Arreglo dinámico de punteros a vértices
        int cant;               //Elementos actuales
        int cap;                //Capacidad reservada
    };

    /* PROTOTIPOS DE FUNCIONES */
    //Prototipos para el grafo
    Graph * Graph_init(void);
    Graph * leerGrafo(const char * ruta, int * dirigido);
    void liberarGrafo(Graph * grafo);
    Vertice * crearVertice(int dato);
    Arista * crearArista(Vertice * destino, int peso);
    int addVertice(Graph * grafo, Vertice * origen, int dato, int peso);

    //Prototipos para la pila
    Stack * Stack_init(void);
    int Stack_void(Stack * pila);       //Devuelve 1 si la pila tiene elementos
    void push(Stack * pila, Vertice * vertice);
    Vertice * pop(Stack * pila);
    void Stack_free(Stack * pila);

    //Prototipos para el recorrido
    int visitado(Stack * visitados, Vertice * nodo);
    Vertice * dfs(Graph * grafo, int dato);

    //Prototipos para el MST
    Arco * kruskal(Graph * grafo, int * cant);  //Devuelve las aristas del MST; *cant = cuántas son

#endif
