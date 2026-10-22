#include "Header.h"

// FUNCION PARA GENERAR LA MATRIZ DE ADYACENCIA: m[i][j] = 1 SI HAY ARISTA i-j
int **generar_matriz(Grafo *g)
{
    int **m = (int**) calloc(g->n, sizeof(int*));
    if(m == NULL)
        return NULL;
    for(int i = 0; i < g->n; i++){
        // CALLOC INICIALIZA CADA RENGLON EN CEROS
        m[i] = (int*) calloc(g->n, sizeof(int));
        if(m[i] == NULL){
            // LIBERAR LOS RENGLONES YA RESERVADOS
            liberar_matriz(m, i);
            return NULL;
        }
    }
    // MARCAR CADA ARISTA USANDO EL INDICE DEL VECINO
    for(int i = 0; i < g->n; i++)
        for(int k = 0; k < g->vertices[i]->grado; k++)
            m[i][buscar_vertice(g, g->vertices[i]->adyacentes[k]->dato)] = 1;
    return m;
}

// FUNCION PARA IMPRIMIR LA MATRIZ DE ADYACENCIA CON ENCABEZADOS
void imprimir_matriz(Grafo *g, int **m)
{
    printf("\nMATRIZ DE ADYACENCIA\n%6s", "");
    for(int j = 0; j < g->n; j++)
        printf("%6d", g->vertices[j]->dato);
    printf("\n");
    for(int i = 0; i < g->n; i++){
        printf("%6d", g->vertices[i]->dato);
        for(int j = 0; j < g->n; j++)
            printf("%6d", m[i][j]);
        printf("\n");
    }
}

// FUNCION PARA LIBERAR LA MATRIZ (RENGLON POR RENGLON Y LUEGO EL ARREGLO)
void liberar_matriz(int **m, int n)
{
    if(m == NULL)
        return;
    for(int i = 0; i < n; i++)
        free(m[i]);
    free(m);
}
