#include "Merge.h"

// DEFINICIÓN (reserva de memoria) de los contadores declarados como extern en Merge.h
long comparaciones = 0;
long id_caso = 0;

// PARÁMETROS DEL EXPERIMENTO PARA GRAFICAR
// Se ordenan N_CASOS arreglos de tamaños TAM_MAX/N_CASOS, 2*TAM_MAX/N_CASOS, ... , TAM_MAX
// OJO CON LOS NÚMEROS: cada caso reserva 2 arreglos (datos + temporal) de 4 bytes por entero,
// ... así que TAM_MAX = 10,000,000 pediría 80 MB y sumaría ~10 mil millones de comparaciones
// ... (varios minutos). Con 1,000,000 la curva n·log(n) ya se ve igual de clara y tarda segundos.
// Se pueden cambiar desde la línea de comandos: ./merge --graficar 100 10000000
#define N_CASOS  20
#define TAM_MAX  1000000
#define ARCHIVO_CSV "merge.csv"

//Ordena los números que llegan por la línea de comandos y los imprime
static int modo_ordenar(int argc, char **argv);
//Corre el experimento completo y deja los resultados en el CSV
static int modo_graficar(int n_casos, long tam_max);

int main(int argc, char ** argv){

    // Sin argumentos -> corremos el experimento con los valores por defecto
    if (argc == 1)
        return modo_graficar(N_CASOS, TAM_MAX);

    // ./merge --graficar [n_casos] [tam_max] -> experimento con parámetros propios
    if (strcmp(argv[1], "--graficar") == 0){
        int  n_casos = (argc > 2) ? atoi(argv[2]) : N_CASOS;
        long tam_max = (argc > 3) ? atol(argv[3]) : TAM_MAX;
        if (n_casos <= 0 || tam_max <= 0){
            printf("Uso: %s --graficar [n_casos] [tam_max]\n", argv[0]);
            return 1;
        }
        return modo_graficar(n_casos, tam_max);
    }

    // Cualquier otra cosa se interpreta como la lista de números a ordenar
    return modo_ordenar(argc, argv);
}

static int modo_ordenar(int argc, char **argv){

    // argv[0] es el nombre del programa, así que los datos son argc-1
    int cant = argc - 1;

    //SI LA CANTIDAD DE ELEMENTOS ES MENOR A 2, ENTONCES NO ES UN ARREGLO, ES SOLO UN NÚMERO
    // Se valida ANTES de declarar el arreglo: en C un arreglo de tamaño 0 o negativo
    // ... es comportamiento indefinido, y la versión original lo llenaba antes de validar
    if (cant < 2){
        printf("Se necesitan al menos 2 números para ordenar.\n");
        return 1;
    }

    // Declaración de un arreglo de enteros para guardar los números que vienen como texto
    int arr[cant];

    // Ciclo para convertir cada dato char a int y guardarlo en el arreglo
    for (int i = 0 ; i < cant ; i++)
        arr[i] = atoi(argv[i+1]);

    init_conteo(cant);              //Reinicia el contador para este ordenamiento
    if (!merge_sort(arr, cant))
        return 1;

    printf("[ %d", arr[0]);
    for (int i = 1 ; i < cant ; i++)
        printf(", %d", arr[i]);
    printf(" ]\n");
    printf("Comparaciones: %ld\n", get_conteo());

    return 0;
}

static int modo_graficar(int n_casos, long tam_max){

    //PASOS PARA GRAFICAR

    // Semilla del generador aleatorio. Es NULL en mayúsculas (null no existe en C) y,
    // ... si no se llama, rand() devuelve SIEMPRE la misma secuencia en cada ejecución
    srand((unsigned)time(NULL));

    // El CSV se abre en modo "a" (append) al guardar cada caso, así que si no lo borramos
    // ... al inicio los resultados de corridas anteriores se acumularían y la gráfica saldría mezclada
    limpiar_archivo_conteo(ARCHIVO_CSV);

    // Tamaños de prueba: n_casos valores repartidos parejo entre tam_max/n_casos y tam_max.
    // Se calculan con long porque tam_max puede pasarse de lo que aguanta un int
    long *casos = (long*)malloc((size_t)n_casos * sizeof(long));
    if (casos == NULL){
        printf("No hay memoria para la tabla de casos.\n");
        return 1;
    }
    for (int i = 0 ; i < n_casos ; i++)
        casos[i] = (tam_max / n_casos) * (i + 1);

    // AQUÍ ESTABA EL ERROR PRINCIPAL: "i , 100" usa el operador coma y evalúa 100,
    // ... que siempre es verdadero -> ciclo infinito. La condición correcta es "i < n_casos"
    for (int i = 0 ; i < n_casos ; i++){

        init_conteo(casos[i]);                          //1. Pone el contador en 0 y anota el tamaño del caso
        int *arreglo = random_arreglo(casos[i]);        //2. Genera datos aleatorios (el caso promedio)
        if (arreglo == NULL){
            printf("No hay memoria para n = %ld\n", casos[i]);
            break;
        }

        // 3. Ordena el arreglo COMPLETO. La firma es (arreglo, cantidad): la del código
        // ... anterior, merge(arr, n, sizeof(int), comparar), es el prototipo de qsort,
        // ... no el de este merge sort
        if (!merge_sort(arreglo, (int)casos[i])){
            free(arreglo);
            break;
        }

        guardar_archivo_conteo(ARCHIVO_CSV);            //4. Escribe la línea "n, comparaciones"
        free(arreglo);                                  //5. Devuelve la memoria: sin esto se acumulan cientos de MB

        printf("n = %ld -> %ld comparaciones\n", casos[i], get_conteo());
    }

    free(casos);
    printf("Listo. Resultados en %s (grafícalos con: python3 plot.py)\n", ARCHIVO_CSV);
    return 0;
}

int merge_sort(int arr[], int n){

    if (n < 2) return 1;        //Un arreglo de 0 o 1 elementos ya está ordenado

    //VARIABLE AUXILIAR: el merge necesita un espacio aparte donde ir dejando la mezcla.
    // Se pide con malloc y no como arreglo local porque para millones de datos
    // ... la pila del programa (unos pocos MB) se desbordaría
    int *temp = (int*)malloc((size_t)n * sizeof(int));
    if (temp == NULL) return 0;

    //GENERACIÓN DE PILA PARA EL DESARROLLO DEL MERGE
    // Simula la recursión: en vez de que el merge sort se llame a sí mismo, guardamos
    // ... en la pila los tramos pendientes junto con la fase en la que va cada uno
    Pila pila;
    inicializar_pila(&pila);
    push(&pila, 0, n-1, DIVIDIR);

    while (!pila_vacia(&pila)){
        Nodo * m = pop(&pila);

        if (m->izq < m->der){
            int med = m->izq + (m->der - m->izq) / 2;   //Punto medio sin riesgo de desbordar (izq+der)/2

            if (m->fase == DIVIDIR){
                // Se apila en orden INVERSO al que queremos ejecutar, porque la pila es LIFO:
                // ... el MERGE va hasta el fondo para que se ejecute al final, cuando las dos
                // ... mitades ya estén ordenadas
                push(&pila, m->izq, m->der, MERGE);
                push(&pila, med + 1, m->der, DIVIDIR);
                push(&pila, m->izq, med, DIVIDIR);
            }
            else
                merge(arr, temp, m->izq, med, m->der);
        }

        // pop() sólo desengancha el nodo de la pila; liberarlo es responsabilidad de quien
        // ... lo saca. Sin este free se fugaba un nodo por cada tramo procesado
        free(m);
    }

    vaciar(&pila);
    free(temp);
    return 1;
}

void merge(int arr[], int temp[], int izq, int med, int der){
    int i = izq;        //Recorre la mitad izquierda
    int j = med+1;      //Recorre la mitad derecha
    int k = izq;        //Posición donde escribimos en temp

    // Mientras queden elementos en AMBAS mitades hay que compararlos: este es el
    // ... único punto donde ocurre una comparación entre datos, por eso se cuenta aquí
    while(i <= med && j <= der){
        incr_conteo();
        temp [k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    }

    // Cuando una mitad se agota, el resto de la otra ya está ordenado: se copia tal cual
    // ... (sin comparar, por eso estos ciclos no incrementan el contador)
    while( i <= med )
        temp[k++] = arr[i++];
    while( j <= der )
        temp[k++] = arr[j++];

    // Se devuelve al arreglo original SÓLO el tramo trabajado [izq..der]
    for (k = izq ; k <= der ; k++)
        arr[k] = temp[k];
}

int* random_arreglo(long n){
    int *arr = (int*)malloc((size_t)n * sizeof(int));
    if (arr == NULL) return NULL;

    // Datos desordenados al azar = caso promedio del algoritmo, que es lo que queremos medir.
    // (rand() sólo llega hasta RAND_MAX = 32767 en algunos sistemas; para la gráfica no
    // ... importa el rango de los valores, sólo que estén desordenados)
    for (long i = 0 ; i < n ; i++)
        arr[i] = rand();

    return arr;
}


void init_conteo(long n ){
    comparaciones = 0;      //Cada caso empieza a contar desde cero
    id_caso = n;            //Guardamos el tamaño para escribirlo después en el CSV
}
void incr_conteo(void){
    comparaciones++;
}
long get_conteo(void){
    return comparaciones;
}
void limpiar_archivo_conteo(const char *const path){
    FILE *archivo = fopen(path, "w");   //"w" TRUNCA el archivo: lo deja vacío
    if (archivo == NULL) return;
    fclose(archivo);
}
void guardar_archivo_conteo(const char *const path){
    FILE *archivo = fopen(path, "a");   //"a" AÑADE al final, para ir acumulando los casos
    if (archivo == NULL) return;        //Si no se puede abrir, fprintf con NULL revienta el programa
    fprintf(archivo, "%ld,%ld\n", id_caso, comparaciones);
    fclose(archivo);
}
