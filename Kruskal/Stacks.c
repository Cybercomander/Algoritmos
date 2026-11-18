#include "Header.h"

Stack * Stack_init(void){
    //Inicializar pila en el heap
    Stack * pila = (Stack*)calloc(1, sizeof(Stack));
    if(pila == NULL)
        printf("\n NO se pudo inicializar la pila");

    return pila;
}

//Devuelve 1 si la pila tiene elementos, 0 si está vacía
int Stack_void(Stack * pila){
    return pila->cant > 0;
}

void push(Stack * pila, Vertice * vertice){
    if(pila->cant == pila->cap){
        int nueva = pila->cap ? pila->cap * 2 : 16;
        Vertice ** tmp = realloc(pila->datos, nueva * sizeof(Vertice*));
        if(tmp == NULL){
            printf("\n No se pudo crecer la pila");
            return;
        }
        pila->datos = tmp;
        pila->cap = nueva;
    }
    pila->datos[pila->cant++] = vertice;
}

//Devuelve el último vértice agregado, o NULL si la pila está vacía
Vertice * pop(Stack * pila){
    if(pila->cant == 0)
        return NULL;

    return pila->datos[--pila->cant];
}

void Stack_free(Stack * pila){
    if(pila == NULL)
        return;
    free(pila->datos);
    free(pila);
}
