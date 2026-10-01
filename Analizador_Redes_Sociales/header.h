#ifndef HEADER_H
#define HEADER_H

    #include <stdio.h>
    #include <math.h>
    #include <stdlib.h>

    typedef struct User{
        char nombre[255];
        int id;
        int grado;
        User * next;
        User * anterior;
    }User;
    
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
        User * top;
        int cant;
    }Pila;

   //PILAS
    User* crear_nodo(int izq, int der, Fase fasear);
    void inicializar_pila(Pila*);
    int push(Pila* pila, int izq, int der, Fase fase);
    User * pop(Pila*);
    int pila_vacia(Pila* );
    void vaciar(Pila*);


#endif