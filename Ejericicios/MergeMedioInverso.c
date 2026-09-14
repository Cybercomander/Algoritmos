#include "MergeMedioInverso.h"

int main(int argc, char ** argv){

    // Se reduce argc porque argv[0] es el nombre del programa
    argc = argc-1;

    // Declaración de un arreglo de entero generados para guardar los números en char
    // ... proporcionados por el parámetro char argv
    int arr[argc];

    // Cliclo para convertir cada dato char a int y guardarlo en el arreglo
    for (int i = 0 ; i < argc ; i++){
        arr[i] = atoi(argv[i+1]);
    }
    
    //SI LA CANTIDAD DE ELEMENTOS ES MENOR A 2, ENTONCES NO ES UN ARREGLO, ES SOLO UN NÚMERO
    if (argc < 2)
        return 1;

    //VARIABLE AUXILIAR
    int temp[argc];

    //GENERACIÓN DE PILA PARA EL DESARROLLO DEL MERGE
    Pila pila;
    inicializar_pila(&pila);
    push(&pila, 0, argc-1, DIVIDIR);

    // PROCESAMIENTO ITERATIVO DE LA PILA
    while (!pila_vacia(&pila)){
        // Extrae un nodo de la pila para procesar
        Nodo * m = pop(&pila);
        // Si el intervalo es inválido, continúa con el siguiente nodo
        if (m->izq >= m->der) continue;
        // Calcula el punto medio del intervalo
        int med = m->izq + (m->der - m->izq) / 2;
        if (m->fase == DIVIDIR){
            // Apila las operaciones en orden inverso para procesar en el orden correcto
            push(&pila, m->izq, m->der, MERGE);
            push(&pila, med + 1, m->der, DIVIDIR);
            push(&pila, m->izq, med, DIVIDIR);
        }
        else
            // Fase de merge: combina los subarreglos ordenados
            merge(&arr[0], &temp[0], m->izq, m->izq + (m->der - m->izq) / 2, m->der);
    }
    // Libera la memoria de la pila
    vaciar(&pila);

    // IMPRESIÓN DEL ARREGLO ORDENADO
    printf("[ %d", arr[0]);
    for (int i = 1 ; i < argc ; i++)
        printf(", %d", arr[i]);
    printf(" ]");

    return 0;
}

// FUNCIÓN MERGE: COMBINA DOS SUBARREGLOS ORDENADOS
void merge(int arr[], int temp[], int izq, int med, int der){
    // Puntero para la parte izquierda del subarreglo
    int i = izq;
    // Puntero para la parte derecha del subarreglo
    int j = med+1;
    // Puntero para el arreglo temporal
    int k = izq;

    // Combina los elementos de ambas partes en orden ascendente
    while(i <= med && j <= der)
        temp [k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    // Copia los elementos restantes de la parte izquierda
    while( i <= med )
        temp[k++] = arr[i++];
    // Copia los elementos restantes de la parte derecha
    while( j <= der )
        temp[k++] = arr[j++];

    // Copia el resultado del arreglo temporal al arreglo original
    for (k = izq ; k <= der ; k++)
        arr[k] = temp[k];
}