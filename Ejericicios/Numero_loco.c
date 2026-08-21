#include <stdio.h>
#include <math.h>
#include <locale.h>

// Código generado en la case para encontrar números locos
int main(void){

    //Declaración de variables
    int a, z, x, y, arr[20], i, j;

    // Inserción de número por parte del usuario
    printf("Ingresa un número: \n");
    fflush(stdin);
    scanf("%d", &x);

    // Declaramos la variable Z con el valor ingresado por el usuario
    z = x;
    // Declaramos a, que nos ayuda para contener el resultado de la comprobación del número loco
    a=0;

    // Para obtener la cantidad de dígitos de un número, se puede aplicar la siguiente fórmula:
    // log10 (número) + 1 = cantidad de dígitos de un número
    // El valor se tiene que almacenar como un double, pues el tipo de dato que retorna la func log()
    double k = log10(x) + 1;
    // Establecemos el conteo de dígitos en int
    i = k;

    //  Inicio de cliclo para ordenamiento de dígitos en arreglo y determinación de número loco
    // Inicia en 0, hasta completar la cantidad de dígitos que contiene el número ingresado
    for (j=0 ; j <= i ; j++){
        // La fórmula para obtener el último dígito de un número es la siguiente: número % 10 
        // Establecemos y para obtener el último dígito del número ingresado
        y = x % 10;
        // Establecemos un arreglo para alojar de manera inversa (<-) los dígitos del número ingresado
        // De esta manera nos aseguramosde que el arreglo quede ordenado correctamente
        arr[i-j] = y;
        // Después de guardar el último dígito, es necesario dividir el número /10 para que el siguiente dígito...
        // ... antes del punto decimal sea el anterior penúltimo número, y así seguir con el ciclo.
        x = x/10;

        // La variable que almacena el número loco, resuelve su identidad con la siguiente expresión de ejemplo
        // 153 = 1ˆ3 + 5ˆ3 + 3ˆ3
        a = a + pow(arr[i-j], i);
    }

    // Impresiones de prueba para determinar la funcionalidad del algoritmo en las variables
    printf("%d \n", a);
    printf("%d \n", z);

    //Impresión de resultados.
    if (a == z)
        printf("Número loco");
    else 
        printf("Número normal");

    return 0;
}