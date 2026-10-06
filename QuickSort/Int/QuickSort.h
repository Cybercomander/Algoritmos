#ifndef QUICKSORT_H
#define QUICKSORT_H

    #include <stdio.h>
    #include <stdlib.h>

    //ESTRUCTURA DE NODO PARA LAS PILAS
    //A DIFERENCIA DEL MERGE, AQUÍ NO HACE FALTA LA FASE : EL TRABAJO (PARTICIÓN)
    //... SE HACE ANTES DE APILAR LOS SUB-ARREGLOS, NO DESPUÉS
    typedef struct Nodo{
        int izq;
        int der;
        struct Nodo *sig;
    }Nodo;

    //ESTRUCTURA DE PILAS
    typedef struct Pila{
        Nodo* top;
        int cant;
    }Pila;

    //PILAS
    Nodo* crear_nodo(int izq, int der);
    void inicializar_pila(Pila*);
    int push(Pila* pila, int izq, int der);
    Nodo* pop(Pila*);
    int pila_vacia(Pila* );
    void vaciar(Pila*);

    //FUNCIONES PARA EL QUICK SORT

    void quickSort(int arr[], int n);
    int particion(int arr[], int izq, int der);
    void swap(int arr[], int i, int j);

#endif
