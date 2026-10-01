#ifndef PILA_H
#define PILA_H

    #include "Header.h"

    //ESTRUCTURA DE NODO PARA LAS PILAS
    typedef struct Nodo{
        User * userIzq;
        User * userDer;
        Fase fase;
        struct Nodo *sig;
    }Nodo;

    typedef enum{
        DIVIDIR,
        MERGE
    }Fase;

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