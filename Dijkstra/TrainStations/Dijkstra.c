#include "Header.h"

/* ============================== GRAFO ============================== */

Graph * Graph_init(void){
    Graph * grafo = (Graph*)calloc(1, sizeof(Graph));
    if(grafo == NULL){
        printf("\n No se pudo generar el grafo");
        return NULL;
    }

    grafo->grado = 0;
    grafo->nodos = NULL;
    grafo->vertices = Stack_init();

    return grafo;
}

//Libera el grafo: las listas de aristas, los vértices (registrados en grafo->vertices) y el grafo
void liberarGrafo(Graph * grafo){
    if(grafo == NULL)
        return;
    if(grafo->vertices != NULL){
        for(int i = 0; i < grafo->vertices->cant; i++){
            free(grafo->vertices->datos[i]->lista);
            free(grafo->vertices->datos[i]);
        }
    }
    Stack_free(grafo->vertices);
    free(grafo);
}

//Crea un vértice en el heap y lo registra en el grafo; el primero creado es el inicio (grafo->nodos)
Vertice * crearVertice(Graph * grafo, const char * nombre){
    Vertice * vertice = (Vertice *)calloc(1, sizeof(Vertice));
    if(vertice == NULL){
        printf("\n No se pudo generar un vértice");
        return NULL;
    }

    strncpy(vertice->nombre, nombre, MAX_NOMBRE - 1);
    vertice->lista = NULL;
    vertice->nexo = 0;
    vertice->distancia = INFINITO;
    vertice->previo = NULL;
    vertice->visitado = 0;

    push(grafo->vertices, vertice);
    grafo->grado++;
    if(grafo->nodos == NULL)
        grafo->nodos = vertice;

    return vertice;
}

//Busca por nombre en el registro de vértices (no depende de que el vértice sea alcanzable)
Vertice * buscarVertice(Graph * grafo, const char * nombre){
    for(int i = 0; i < grafo->vertices->cant; i++)
        if(strcmp(grafo->vertices->datos[i]->nombre, nombre) == 0)
            return grafo->vertices->datos[i];
    return NULL;
}

//Agrega la arista dirigida origen -> destino con su peso; devuelve 1 si tuvo éxito
int addArista(Graph * grafo, const char * origen, const char * destino, int peso){
    Vertice * v = buscarVertice(grafo, origen);
    Vertice * d = buscarVertice(grafo, destino);
    if(v == NULL || d == NULL){
        printf("\n No se encontró el vértice %s", v == NULL ? origen : destino);
        return 0;
    }

    Arista * tmp = realloc(v->lista, (v->nexo + 1) * sizeof(Arista));
    if(tmp == NULL){
        printf("\n No se pudo realloc en lista");
        return 0;
    }

    v->lista = tmp;
    v->lista[v->nexo].destino = d;
    v->lista[v->nexo].peso = peso;
    v->nexo++;

    return 1;
}

/* ============================== PILA ============================== */

Stack * Stack_init(void){
    //Inicializar pila en el heap
    Stack * pila = (Stack*)calloc(1, sizeof(Stack));
    if(pila == NULL)
        printf("\n NO se pudo inicializar la pila");

    return pila;
}

//Devuelve 1 si la pila tiene elementos, 0 si está vacía
int Stack_void(Stack * pila){
    return pila->cant > 0;
}

//Insertar un vértice en la pila para el recorrido DFS
void push(Stack * pila, Vertice * vertice){
    if(pila->cant == pila->cap){
        int nueva = pila->cap ? pila->cap * 2 : 16;
        Vertice ** tmp = realloc(pila->datos, nueva * sizeof(Vertice*));
        if(tmp == NULL){
            printf("\n No se pudo crecer la pila");
            return;
        }
        pila->datos = tmp;
        pila->cap = nueva;
    }
    pila->datos[pila->cant++] = vertice;
}

//Devuelve el último vértice agregado, o NULL si la pila está vacía
Vertice * pop(Stack * pila){
    if(pila->cant == 0)
        return NULL;

    return pila->datos[--pila->cant];
}

void Stack_free(Stack * pila){
    if(pila == NULL)
        return;
    free(pila->datos);
    free(pila);
}

/* ============================== HEAP ============================== */
/* Min-heap binario guardado en arreglo: el padre de i es (i-1)/2 y sus hijos 2i+1 y 2i+2.
   La raíz (datos[0]) siempre es el nodo con menor distancia. */

Heap * Heap_init(void){
    Heap * heap = (Heap*)calloc(1, sizeof(Heap));
    if(heap == NULL)
        printf("\n NO se pudo inicializar el heap");

    return heap;
}

//Devuelve 1 si el heap tiene elementos, 0 si está vacío
int Heap_void(Heap * heap){
    return heap->cant > 0;
}

//Intercambia dos nodos del heap
static void intercambiar(NodoHeap * a, NodoHeap * b){
    NodoHeap tmp = *a;
    *a = *b;
    *b = tmp;
}

//Inserta al final y "sube" el nodo mientras sea menor que su padre
void Heap_push(Heap * heap, Vertice * vertice, int distancia){
    if(heap->cant == heap->cap){
        int nueva = heap->cap ? heap->cap * 2 : 16;
        NodoHeap * tmp = realloc(heap->datos, nueva * sizeof(NodoHeap));
        if(tmp == NULL){
            printf("\n No se pudo crecer el heap");
            return;
        }
        heap->datos = tmp;
        heap->cap = nueva;
    }

    int i = heap->cant++;
    heap->datos[i].vertice = vertice;
    heap->datos[i].distancia = distancia;

    while(i > 0 && heap->datos[(i - 1) / 2].distancia > heap->datos[i].distancia){
        intercambiar(&heap->datos[i], &heap->datos[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

//Extrae la raíz, mueve el último nodo arriba y lo "baja" hasta su lugar
NodoHeap Heap_pop(Heap * heap){
    NodoHeap raiz = heap->datos[0];
    heap->datos[0] = heap->datos[--heap->cant];

    int i = 0;
    while(1){
        int menor = i;
        int izq = 2 * i + 1;
        int der = 2 * i + 2;

        if(izq < heap->cant && heap->datos[izq].distancia < heap->datos[menor].distancia)
            menor = izq;
        if(der < heap->cant && heap->datos[der].distancia < heap->datos[menor].distancia)
            menor = der;
        if(menor == i)
            break;

        intercambiar(&heap->datos[i], &heap->datos[menor]);
        i = menor;
    }

    return raiz;
}

void Heap_free(Heap * heap){
    if(heap == NULL)
        return;
    free(heap->datos);
    free(heap);
}

/* ============================== DFS ============================== */

//Devuelve 1 si el nodo ya está en la pila de visitados, 0 si no
int visitado(Stack * visitados, Vertice * nodo){
    for(int i = 0; i < visitados->cant; i++)
        if(visitados->datos[i] == nodo)
            return 1;
    return 0;
}

//Recorrido en profundidad desde inicio; devuelve el vértice con ese nombre si es alcanzable
//Devuelve NULL si el nodo origen no está conectado con el nodo de destino
Vertice * dfs(Graph * grafo, Vertice * inicio, const char * nombre){
    if(grafo == NULL || inicio == NULL)
        return NULL;

    Stack * pila = Stack_init();        //Nodos pendientes por explorar
    Stack * visitados = Stack_init();   //Nodos ya explorados
    if(pila == NULL || visitados == NULL){
        Stack_free(pila);
        Stack_free(visitados);
        return NULL;
    }

    Vertice * encontrado = NULL;
    push(pila, inicio);

    while(Stack_void(pila)){
        Vertice * nodo = pop(pila);
        if(visitado(visitados, nodo))   //Pudo entrar varias veces a la pila
            continue;
        push(visitados, nodo);

        if(strcmp(nodo->nombre, nombre) == 0){
            encontrado = nodo;
            break;
        }

        //Se agregan los vecinos en orden inverso para visitarlos en su orden original
        for(int i = nodo->nexo - 1; i >= 0; i--){
            Vertice * vecino = nodo->lista[i].destino;
            if(!visitado(visitados, vecino))
                push(pila, vecino);
        }
    }

    Stack_free(pila);
    Stack_free(visitados);
    return encontrado;
}

/* ============================== DIJKSTRA ============================== */

/* Calcula el camino de menor costo desde origen hacia todos los vértices.
   Al terminar, cada vértice tiene su distancia mínima y en previo el vértice anterior del camino.
   Se usa "inserción perezosa": un vértice puede entrar varias veces al heap, y las
   entradas obsoletas se descartan al salir porque el vértice ya está visitado. */
void dijkstra(Graph * grafo, Vertice * origen){
    //Reiniciar el estado de todos los vértices
    for(int i = 0; i < grafo->vertices->cant; i++){
        Vertice * v = grafo->vertices->datos[i];
        v->distancia = INFINITO;
        v->previo = NULL;
        v->visitado = 0;
    }

    Heap * heap = Heap_init();
    if(heap == NULL)
        return;

    origen->distancia = 0;
    Heap_push(heap, origen, 0);

    while(Heap_void(heap)){
        Vertice * actual = Heap_pop(heap).vertice;   //El más barato aún no fijado
        if(actual->visitado)
            continue;
        actual->visitado = 1;

        //Relajación: si pasar por actual abarata llegar al vecino, se actualiza
        for(int i = 0; i < actual->nexo; i++){
            Vertice * vecino = actual->lista[i].destino;
            int nueva = actual->distancia + actual->lista[i].peso;

            if(!vecino->visitado && nueva < vecino->distancia){
                vecino->distancia = nueva;
                vecino->previo = actual;
                Heap_push(heap, vecino, nueva);
            }
        }
    }

    Heap_free(heap);
}

//Imprime el camino siguiendo los previos desde destino hasta el origen (usando la pila para invertirlo)
void imprimirCamino(Vertice * destino){
    if(destino->distancia == INFINITO){
        printf("No existe camino hacia %s\n", destino->nombre);
        return;
    }

    Stack * camino = Stack_init();
    for(Vertice * v = destino; v != NULL; v = v->previo)
        push(camino, v);

    printf("[ ");
    while(Stack_void(camino)){
        Vertice * v = pop(camino);
        printf(Stack_void(camino) ? "%s a " : "%s ", v->nombre);
    }
    printf("]\npeso : %d\n", destino->distancia);

    Stack_free(camino);
}
