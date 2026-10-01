#include "Header.h"

void mergeSort(int arr[], int n){
        //SI LA CANTIDAD DE ELEMENTOS ES MENOR A 2, ENTONCES NO ES UN ARREGLO, ES SOLO UN NÚMERO
    if (n < 2)
        return 1;

    //VARIABLE AUXILIAR
    int temp[n];

    //GENERACIÓN DE PILA PARA EL DESARROLLO DEL MERGE
    Pila pila;
    inicializar_pila(&pila);
    push(&pila, 0, n-1, DIVIDIR);

    while (!pila_vacia(&pila)){
        Nodo * m = pop(&pila);
        if (m->izq >= m->der) continue;
        int med = m->izq + (m->der - m->izq) / 2;
        if (m->fase == DIVIDIR){
            push(&pila, m->izq, m->der, MERGE);
            push(&pila, med + 1, m->der, DIVIDIR);
            push(&pila, m->izq, med, DIVIDIR);
        }
        else
            merge(&arr[0], &temp[0], m->izq, m->izq + (m->der - m->izq) / 2, m->der);
    }
    vaciar(&pila);
}

void merge(int arr[], int temp[], int izq, int med, int der){
    int i = izq;
    int j = med+1;
    int k = izq;

    while(i <= med && j <= der)
        temp [k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    while( i <= med ) 
        temp[k++] = arr[i++];
    while( j <= der ) 
        temp[k++] = arr[j++];

    for (k = izq ; k <= der ; k++)
        arr[k] = temp[k];
}