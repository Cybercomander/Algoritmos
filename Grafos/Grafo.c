#include "Header.h"

int main(void){
    int dato, vecino, aristas;
    Grafo *g;

    // EL GRAFO SIEMPRE EMPIEZA CON UN VERTICE
    printf("Dato del vertice inicial: ");
    if(scanf("%d", &dato) != 1 || (g = crear_grafo(dato)) == NULL){
        printf("No se pudo crear el grafo\n");
        return 1;
    }

    // CADA NUMERO INTRODUCIDO AGREGA SU VERTICE Y SUS ARISTAS
    printf("Nuevo vertice (cualquier letra para terminar): ");
    while(scanf("%d", &dato) == 1){
        Nodo *nuevo = insertarNodo(g, dato);
        if(nuevo == NULL){
            printf("Vertice repetido o sin memoria, se ignora\n");
        }else{
            printf("Numero de aristas de %d: ", dato);
            if(scanf("%d", &aristas) != 1)
                break;
            for(int i = 0; i < aristas; i++){
                printf("  Conectar %d con: ", dato);
                if(scanf("%d", &vecino) != 1)
                    break;
                int idx = buscar_vertice(g, vecino);
                if(idx == -1 || !agregar_arista(nuevo, g->vertices[idx]))
                    printf("  Arista invalida (vertice inexistente, repetida o lazo)\n");
            }
        }
        printf("Nuevo vertice (cualquier letra para terminar): ");
    }

    // GENERAR, MOSTRAR Y LIBERAR LA MATRIZ DE ADYACENCIA
    int **m = generar_matriz(g);
    if(m != NULL)
        imprimir_matriz(g, m);
    liberar_matriz(m, g->n);

    // GENERAR, MOSTRAR Y LIBERAR LA LISTA DE ADYACENCIA
    Elemento **l = generar_lista(g);
    if(l != NULL)
        imprimir_lista(g, l);
    liberar_lista(l, g->n);

    liberar_memoria(g);
    return 0;
}
