#include "Header.h"

// FUNCION PARA GENERAR LA LISTA DE ADYACENCIA: l[i] ES LA LISTA DE VECINOS DEL VERTICE i
Elemento **generar_lista(Grafo *g)
{
    Elemento **l = (Elemento**) calloc(g->n, sizeof(Elemento*));
    if(l == NULL)
        return NULL;
    for(int i = 0; i < g->n; i++){
        Elemento **fin = &l[i];
        // AGREGAR CADA VECINO AL FINAL PARA CONSERVAR EL ORDEN DE INSERCION
        for(int k = 0; k < g->vertices[i]->grado; k++){
            Elemento *e = (Elemento*) calloc(1, sizeof(Elemento));
            if(e == NULL){
                // LIBERAR TODO LO CONSTRUIDO HASTA AHORA
                liberar_lista(l, i + 1);
                return NULL;
            }
            e->dato = g->vertices[i]->adyacentes[k]->dato;
            *fin = e;
            fin = &e->next;
        }
    }
    return l;
}

// FUNCION PARA IMPRIMIR LA LISTA DE ADYACENCIA
void imprimir_lista(Grafo *g, Elemento **l)
{
    printf("\nLISTA DE ADYACENCIA\n");
    for(int i = 0; i < g->n; i++){
        printf("%d", g->vertices[i]->dato);
        for(Elemento *e = l[i]; e != NULL; e = e->next)
            printf(" -> %d", e->dato);
        printf("\n");
    }
}

// FUNCION PARA LIBERAR LA LISTA DE ADYACENCIA (CADA LISTA LIGADA Y LUEGO EL ARREGLO)
void liberar_lista(Elemento **l, int n)
{
    if(l == NULL)
        return;
    for(int i = 0; i < n; i++){
        Elemento *e = l[i];
        while(e != NULL){
            // GUARDAR EL SIGUIENTE ANTES DE LIBERAR EL ACTUAL
            Elemento *sig = e->next;
            free(e);
            e = sig;
        }
    }
    free(l);
}
