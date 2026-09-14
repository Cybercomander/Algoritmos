#include "Merge.h"

Nodo* crear_nodo(int izq, int der, Fase fase) {
    Nodo *nodo = (Nodo*)malloc(sizeof(Nodo));
    if (nodo == NULL) return NULL;      //Sin esto, si falla malloc se escribe sobre un puntero nulo
    nodo->izq = izq;
    nodo->der = der;
    nodo->fase = fase;
    return nodo;
}

void inicializar_pila(Pila *pila) {
    pila->top = NULL;
    pila->cant = 0;
}

int push(Pila* pila, int izq, int der, Fase fase){
    Nodo *nodo = crear_nodo(izq, der, fase);
    if (nodo == NULL) return 0;         //Devuelve 0 para avisar que no se pudo apilar
    nodo->sig = pila->top;
    pila->top = nodo;
    pila->cant++;

    return 1;
}                    

// Devuelve el nodo del tope y lo desengancha. QUIEN LLAMA debe hacerle free()
Nodo* pop(Pila* pila){
    if (pila->top == NULL) return NULL;
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