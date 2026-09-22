#include "QuickSort.h"

Nodo* crear_nodo(int izq, int der) {
    Nodo *nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->izq = izq;
    nodo->der = der;
    return nodo;
}

void inicializar_pila(Pila *pila) {
    pila->top = NULL;
    pila->cant = 0;
}

int push(Pila* pila, int izq, int der){
    Nodo *nodo = crear_nodo(izq, der);
    nodo->sig = pila->top;
    pila->top = nodo;
    pila->cant++;

    return 1;
}

Nodo* pop(Pila* pila){
    Nodo *nodo = pila->top;
    pila->top = nodo->sig;
    pila->cant--;
    return nodo;
}

int pila_vacia(Pila* pila){
    if (pila->top == NULL) {
        return 1;
    }
    return 0;
}

void vaciar(Pila* pila){
    Nodo *nodo = pila->top;
    while (nodo != NULL) {
        pila->top = nodo->sig;
        free(nodo);
        nodo = pila->top;
    }
    pila->cant = 0;
    pila->top = NULL;
}
