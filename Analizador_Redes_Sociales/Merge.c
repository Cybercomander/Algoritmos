#include <stdlib.h>
#include "Merge.h"
#include "Pila.h"

// Funcion para ordenar la lista de usuarios con merge sort iterativo usando una pila
void mergeSort(Lista *lista, Criterio criterio, Orden orden){
    //SI LA CANTIDAD DE ELEMENTOS ES MENOR A 2, LA LISTA YA ESTA ORDENADA
    if (lista->longitud < 2)
        return;

    //GENERACIÓN DE PILA PARA EL DESARROLLO DEL MERGE
    Pila pila;
    inicializar_pila(&pila);
    push(&pila, 0, lista->longitud - 1, DIVIDIR);

    while (!pila_vacia(&pila)){
        Nodo * m = pop(&pila);
        int izq = m->izq;
        int der = m->der;
        Fase fase = m->fase;
        free(m);

        if (izq >= der) continue;
        int med = izq + (der - izq) / 2;
        if (fase == DIVIDIR){
            push(&pila, izq, der, MERGE);
            push(&pila, med + 1, der, DIVIDIR);
            push(&pila, izq, med, DIVIDIR);
        }
        else
            merge(lista, izq, med, der, criterio, orden);
    }
    vaciar(&pila);
}

// Funcion para mezclar las posiciones izq..med y med+1..der reenlazando los nodos de la lista
void merge(Lista *lista, int izq, int med, int der, Criterio criterio, Orden orden){
    User *primero = obtener_usuario(lista, izq);
    User *ultimo_a = obtener_usuario(lista, med);
    User *ultimo = obtener_usuario(lista, der);

    //NODOS FUERA DEL RANGO PARA RECONECTAR AL FINAL
    User *antes = primero->anterior;
    User *despues = ultimo->siguiente;

    //CORTAR LAS DOS CORRIDAS
    User *a = primero;
    User *b = ultimo_a->siguiente;
    ultimo_a->siguiente = NULL;
    ultimo->siguiente = NULL;

    //MEZCLA DE LAS CORRIDAS USANDO UN NODO CENTINELA
    User centinela;
    centinela.siguiente = NULL;
    User *actual = &centinela;

    while (a != NULL && b != NULL){
        if (comparar(a, b, criterio, orden) <= 0){
            actual->siguiente = a;
            a->anterior = actual;
            a = a->siguiente;
        }
        else{
            actual->siguiente = b;
            b->anterior = actual;
            b = b->siguiente;
        }
        actual = actual->siguiente;
    }
    while (a != NULL){
        actual->siguiente = a;
        a->anterior = actual;
        a = a->siguiente;
        actual = actual->siguiente;
    }
    while (b != NULL){
        actual->siguiente = b;
        b->anterior = actual;
        b = b->siguiente;
        actual = actual->siguiente;
    }

    //RECONECTAR EL RANGO MEZCLADO CON EL RESTO DE LA LISTA
    User *nuevo_primero = centinela.siguiente;
    nuevo_primero->anterior = antes;
    if (antes == NULL)
        lista->cabeza = nuevo_primero;
    else
        antes->siguiente = nuevo_primero;

    actual->siguiente = despues;
    if (despues == NULL)
        lista->cola = actual;
    else
        despues->anterior = actual;
}

// Funcion para obtener el usuario que esta en una posicion de la lista
User* obtener_usuario(Lista *lista, int posicion){
    User *actual = lista->cabeza;
    for (int i = 0; i < posicion && actual != NULL; i++)
        actual = actual->siguiente;
    return actual;
}

// Funcion para comparar dos usuarios segun el criterio y el orden
int comparar(User *a, User *b, Criterio criterio, Orden orden){
    int resultado;

    if (criterio == POR_ID)
        resultado = a->id - b->id;
    else
        resultado = a->grado - b->grado;

    //EL ORDEN DESCENDENTE INVIERTE SOLO EL CRITERIO PRINCIPAL
    if (orden == DESCENDENTE)
        resultado = -resultado;

    //DESEMPATE POR ID ASCENDENTE
    if (resultado == 0)
        resultado = a->id - b->id;

    return resultado;
}
