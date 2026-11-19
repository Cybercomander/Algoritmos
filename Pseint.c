#include <stdio.h>
void acomodar_matriz(int filas, int columnas, double matriz[filas][columnas]){

    //variables para la estimación
    // no se puede usar sqrt para la raíz
    double margen = 0.0001;

    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            // Paso 1: tomar el número y dejarlo positivo
            double x = matriz[i][j];
            if (x < 0){
                x = -x;
            }

            // Paso 2: empezar con una estimación
            double estimacion = 1;
            // Paso 3: mejorar la estimación hasta que su cuadrado esté cerca de x
            double cuadrado = estimacion * estimacion;
            while (cuadrado - x > margen || x - cuadrado > margen){
                double cociente = x / estimacion;
                estimacion = (cociente + estimacion) / 2.0;
                cuadrado = estimacion * estimacion;
            }
            // Paso 4: guardar el resultado en la matriz
            matriz[i][j] = estimacion;
        }
    }
}

int main(void){

    // Paso 1: pedir la cantidad de filas y columnas (menor a 20)
    int filas;
    int columnas;

    printf("Cantidad de filas (Máximo 20): ");
    scanf("%d", &filas);

    printf("Cantidad de columnas (Máximo 20): ");
    scanf("%d", &columnas);

    // Paso 2: pedir los datos de la matriz
    double matriz[filas][columnas];
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            printf("Elemento [%d][%d]: ", i + 1, j + 1);
            scanf("%lf", &matriz[i][j]);
        }
    }

    // Paso 3: mostrar la matriz original (antes de modificarla)
    printf("\nMatriz original:\n");
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            printf("%10.4f", matriz[i][j]);
        }
        printf("\n");
    }

    // Paso 4: calcular la raíz de cada elemento
    acomodar_matriz(filas, columnas, matriz);

    // Paso 5: mostrar la matriz raíz
    printf("\nMatriz raiz cuadrada:\n");
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            printf("%10.4f", matriz[i][j]);
        }
        printf("\n");
    }

    return 0;
}
