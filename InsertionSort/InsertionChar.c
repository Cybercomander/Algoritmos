#include "InsertionChar.h"

int main(int argc, char *argv[]){

    if (argc < 2){
        return 1;
    }
    // El tamaño del arreglo es igual a la cantidad de datos de argc -1
    // Esto se debe a que en la posición 0 del arreglo siempre habrá un elemento
    // ...que indica la ruta desde la que se invocó el programa y la cantidad 
    // ... empieza a partir de la posición 1
    int size = argc-1;

    // Declaración de un arreglo de entero generados para guardar los números en char
    // ... proporcionados por el parámetro char argv
    char * arr[size];

    // Cliclo para convertir cada dato char a int y guardarlo en el arreglo
    for (int i = 0 ; i < size ; i++){
        arr[i] = argv[i+1];
    }

    insertion(&arr[0], size);

    for (int i = 0 ; i < size ; i++){
        if (arr[i] == arr[0])
            printf("%s", arr[i]);
        else 
            printf(",%s", arr[i]);
    }

    return 0;
}

void insertion(char * arr[], int n) {
    for (int i = 1; i < n; i++) {
        char tmp = *(arr[i]);      // Se guarda la posición actual 
        int j = i - 1;

        // Ciclo de recorrimiento hacia la derecha para todos los números de la 
        // izquierda mayores al valor temporal tmp
        while (j >= 0 && *(arr[j]) > tmp) {
            *(arr[j + sizeof(char)]) = *(arr[j]);
            j--;
        }

        * (arr[j + sizeof(char)]) = tmp;    // Se restaura el hueco del valor más grande
    }
}