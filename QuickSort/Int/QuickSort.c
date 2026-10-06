#include "QuickSort.h"

int main(int argc, char * argv[]){

    //VARIABLES PARA EL USO DEL ALGORITMO
    const int n = 9;
    int arr[] = {50, 25, 92, 16, 76, 30, 43, 54, 19};

    quickSort(arr, n);

    printf("[ %d", arr[0]);
    for (int i = 1 ; i < n ; i++)
        printf(", %d", arr[i]);
    printf(" ]\n");

    return 0;
}

// Summary : Reglas de validación
/*
    L <= P  : L+1
    R > P   : R-1
    <- L <- R  : L <-> R
    L > R   : P <-> R
*/

void quickSort(int arr[], int n){
    //SI LA CANTIDAD DE ELEMENTOS ES MENOR A 2, ENTONCES NO HAY NADA QUE ORDENAR
    if (n < 2) return;

    //GENERACIÓN DE PILA PARA EL DESARROLLO DEL QUICK
    Pila pila;
    inicializar_pila(&pila);
    push(&pila, 0, n-1);

    while (!pila_vacia(&pila)){
        Nodo * m = pop(&pila);
        int izq = m->izq;
        int der = m->der;
        free(m);

        if (izq >= der) continue;

        //SE PARTICIONA PRIMERO Y LUEGO SE APILAN LOS DOS LADOS
        //... EL PIVOTE YA QUEDÓ EN SU POSICIÓN DEFINITIVA, POR ESO SE EXCLUYE
        int p = particion(arr, izq, der);
        push(&pila, p + 1, der);
        push(&pila, izq, p - 1);
    }
    vaciar(&pila);
}

int particion(int arr[], int izq, int der){
    //EL PIVOTE ES EL PRIMER ELEMENTO DEL SUB-ARREGLO
    int P = izq;
    int L = izq + 1;
    int R = der;

    while (L <= R){

        if (arr[L] <= arr[P])
            L++;

        else if (arr[R] > arr[P])
            R--;

        else
            swap(arr, L, R);
    }

    //L Y R SE CRUZARON : R APUNTA AL ÚLTIMO MENOR O IGUAL AL PIVOTE
    swap(arr, P, R);

    return R;
}

void swap(int arr[], int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
