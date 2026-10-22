#include "Header.h"

// FUNCION PARA CREAR UN NUEVO NODO EN EL GRAFO
Nodo *crear_nodo(int dato)
{
    Nodo *nuevo;
    // RESERVAR MEMORIA PARA EL NUEVO NODO (CALLOC DEJA adyacentes EN NULL Y grado EN 0)
    nuevo = (Nodo*) calloc(1,sizeof(Nodo));
    if(nuevo == NULL)
        return NULL;
    // ASIGNAR EL DATO AL NUEVO NODO
    nuevo->dato = dato;
    return nuevo;
}

// FUNCION PARA CREAR EL GRAFO, SIEMPRE EMPIEZA CON UN VERTICE
Grafo *crear_grafo(int dato)
{
    Grafo *g = (Grafo*) calloc(1,sizeof(Grafo));
    if(g == NULL)
        return NULL;
    if(insertarNodo(g, dato) == NULL){
        free(g);
        return NULL;
    }
    return g;
}

// FUNCION PARA BUSCAR EL INDICE DE UN VERTICE POR SU DATO
int buscar_vertice(Grafo *g, int dato)
{
    for(int i = 0; i < g->n; i++)
        if(g->vertices[i]->dato == dato)
            return i;
    return -1;
}

// FUNCION PARA AGREGAR UN VERTICE AL GRAFO
Nodo *insertarNodo(Grafo *g, int dato)
{
    // NO SE PERMITEN VERTICES REPETIDOS
    if(buscar_vertice(g, dato) != -1)
        return NULL;
    Nodo *nuevo = crear_nodo(dato);
    if(nuevo == NULL)
        return NULL;
    // REASIGNAR CON UN PUNTERO TEMPORAL PARA NO PERDER EL ARREGLO SI REALLOC FALLA
    Nodo **tmp = (Nodo**) realloc(g->vertices, (g->n + 1) * sizeof(Nodo*));
    if(tmp == NULL){
        free(nuevo);
        return NULL;
    }
    g->vertices = tmp;
    g->vertices[g->n++] = nuevo;
    return nuevo;
}

// FUNCION AUXILIAR: AGREGA b A LOS VECINOS DE a (REALLOC DEL ARREGLO DE ADYACENTES)
static int agregar_vecino(Nodo *a, Nodo *b)
{
    Nodo **tmp = (Nodo**) realloc(a->adyacentes, (a->grado + 1) * sizeof(Nodo*));
    if(tmp == NULL)
        return 0;
    a->adyacentes = tmp;
    a->adyacentes[a->grado++] = b;
    return 1;
}

// FUNCION PARA AGREGAR UNA ARISTA NO DIRIGIDA (a <-> b). REGRESA 1 SI SE AGREGO
int agregar_arista(Nodo *a, Nodo *b)
{
    if(a == NULL || b == NULL || a == b)
        return 0;
    // EVITAR ARISTAS DUPLICADAS
    for(int i = 0; i < a->grado; i++)
        if(a->adyacentes[i] == b)
            return 0;
    if(!agregar_vecino(a, b))
        return 0;
    // SI FALLA EL LADO b, DESHACER EL LADO a PARA QUE EL GRAFO QUEDE CONSISTENTE
    if(!agregar_vecino(b, a)){
        a->grado--;
        return 0;
    }
    return 1;
}

// FUNCION PARA LIBERAR LA MEMORIA DEL GRAFO
void liberar_memoria(Grafo *g)
{
    if(g == NULL)
        return;
    for(int i = 0; i < g->n; i++){
        // LIBERAR EL ARREGLO DE VECINOS (LOS VECINOS SE LIBERAN EN SU PROPIA VUELTA)
        free(g->vertices[i]->adyacentes);
        // LIBERAR EL VERTICE ACTUAL
        free(g->vertices[i]);
    }
    // LIBERAR EL ARREGLO DE VERTICES Y EL GRAFO
    free(g->vertices);
    free(g);
}
