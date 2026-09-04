#ifndef MERGESORT_H
#define MERGESORT_H

    #include <stdio.h> 
    #include <stdlib.h>

    typedef enum{
        DIVIDIR,
        MERGE
    }Fase;
    
    //ESTRUCTURA DE NODO PARA LAS PILAS
    typedef struct Nodo{
        int izq;
        int der;
        Fase fase;
        struct Nodo *sig;
    }Nodo;

    //ESTRUCTURA DE PILAS
    typedef struct Pila{
        Nodo* top;
        int cant;
    }Pila;

    //PILAS
    Nodo* crear_nodo(int izq, int der, Fase fasear);
    void inicializar_pila(Pila*);
    int push(Pila* pila, int izq, int der, Fase fase);
    Nodo* pop(Pila*);
    int pila_vacia(Pila* );
    void vaciar(Pila*);

    //FUNCIONES PARA EL MERGE SORT

    void merge(int arr[], int temp[], int izq, int med, int der);

#endif