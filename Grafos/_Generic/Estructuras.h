#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

    // DEFINICIÓN DE _GENERICS
    

    //ESTRUCTURA DE NODO (VÉRTICE PARA EL GRAFO)
    typedef struct vertice{
        struct vertice **listaAdy;
        void * dato;
    }Vertice;

    typedef struct stack{
        void * data;
        void * top;
    }Stack;

    typedef struct cola{
        struct cola bottom;
        struct next;
    }Cola;

    // PROTOTIPOS DE FUNCIONES
    stackInit(void);

#endif