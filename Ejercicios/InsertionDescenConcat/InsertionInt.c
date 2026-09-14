#include "Insertionint.h"

int main(void){

    int arr1[3] = {3,5,1};
    int arr2[3] = {0,43,0};

    // ORDENAR ARREGLOS DESCENDENTE
    printf("\nArreglos: ");
    insertion(&arr1[0], sizeof(arr1)/sizeof(int));
    insertion(&arr2[0], sizeof(arr2)/sizeof(int));

    // CONCATENAR ARREGLOS EN UN SOLO NÚMERO
    printf("\nNumeros concatenados: ");
    int num1 = concat(&arr1[0], sizeof(arr1)/sizeof(int));
    int num2 = concat(&arr2[0], sizeof(arr2)/sizeof(int));

    // SUMAR AMBOS NÚMEROS
    printf("\nResultado : %d", num1 + num2);

    return 0;
}

void insertion(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int tmp = arr[i];      // Se guarda la posición actual 
        int j = i - 1;

        // Ciclo de recorrimiento hacia la derecha para todos los números de la 
        // izquierda mayores al valor temporal tmp
        while (j >= 0 && arr[j] < tmp) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = tmp;      // Se restaura el hueco del valor más grande
    }

        // Ciclo de impresión 
    printf("\n[ ");
    for (int i = 0 ; i < n ; i++){
        if (arr[i] == arr[0])
            printf("%d", arr[i]);
        else 
            printf(", %d", arr[i]);
    }
    printf(" ]");
}

int concat(int arr[], int n ){
    int concatenado = 0;
    for (int i = 0 ; i < n ; i++)
        concatenado = concatenado*10 + arr[i];

    printf("\n%d", concatenado);
    return concatenado;
}