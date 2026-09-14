#ifndef MERGESORT_H
#define MERGESORT_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>     //NECESARIO PARA strcmp() AL LEER LAS OPCIONES DE LA LÍNEA DE COMANDOS
    #include <time.h>       //NECESARIO PARA time() QUE USAMOS COMO SEMILLA DE srand()

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

    //Mezcla dos mitades YA ORDENADAS: [izq..med] y [med+1..der]
    void merge(int arr[], int temp[], int izq, int med, int der);

    //Ordena el arreglo COMPLETO (divide con la pila y mezcla). Devuelve 1 si pudo, 0 si falló la memoria
    int merge_sort(int arr[], int n);


    // FUNCIONES ADICIONALES DE LA CLASE PARA GRAFICAR

    //Genera un arreglo de n enteros aleatorios (hay que liberarlo con free)
    int* random_arreglo(long n);

    //Interfaces para contar pasos
    void init_conteo(long n);
    void incr_conteo(void);
    void guardar_archivo_conteo(const char *const path);
    void limpiar_archivo_conteo(const char *const path);
    long get_conteo(void);      //DEVUELVE UN long, NO void: si no, no puede retornar el contador

    // OJO: en el .h van sólo DECLARACIONES (extern). Si aquí escribiéramos "long comparaciones;"
    // ... cada .c que incluya el header crearía su propia variable y el enlazador daría
    // ... "duplicate symbol". La DEFINICIÓN real de estas dos variables está en Merge.c
    extern long comparaciones;  //Cuántas comparaciones lleva el caso actual
    extern long id_caso;        //Cuántos datos tiene el caso actual (el eje X de la gráfica)

#endif
