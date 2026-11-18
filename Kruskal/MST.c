#include "Header.h"

// Algoritmo para determinar MST del grafo.

//Recolecta todos los vértices del grafo: los registrados y los alcanzables desde nodos.
//Solo se siguen arcos de salida, pero los registrados entran todos, así que
//los vértices que solo reciben arcos también quedan incluidos.
static Stack * recolectar(Graph * grafo){
    Stack * pendientes = Stack_init();
    Stack * vistos = Stack_init();
    if(pendientes == NULL || vistos == NULL){
        Stack_free(pendientes);
        Stack_free(vistos);
        return NULL;
    }

    if(grafo->nodos != NULL)
        push(pendientes, grafo->nodos);
    if(grafo->vertices != NULL)
        for(int i = 0; i < grafo->vertices->cant; i++)
            push(pendientes, grafo->vertices->datos[i]);

    while(Stack_void(pendientes)){
        Vertice * nodo = pop(pendientes);
        if(visitado(vistos, nodo))
            continue;
        push(vistos, nodo);

        for(int i = 0; i < nodo->nexo; i++)
            if(!visitado(vistos, nodo->lista[i].destino))
                push(pendientes, nodo->lista[i].destino);
    }

    Stack_free(pendientes);
    return vistos;
}

//Orden ascendente por peso para qsort
static int cmp_peso(const void * a, const void * b){
    const Arco * x = a;
    const Arco * y = b;
    return (x->peso > y->peso) - (x->peso < y->peso);
}

//Union-find: devuelve la raíz del conjunto de x, con compresión de caminos
static int buscar(int * padre, int x){
    while(padre[x] != x){
        padre[x] = padre[padre[x]];
        x = padre[x];
    }
    return x;
}

//Posición del vértice dentro de la lista de vértices (-1 si no está)
static int indice(Stack * vertices, Vertice * v){
    for(int i = 0; i < vertices->cant; i++)
        if(vertices->datos[i] == v)
            return i;
    return -1;
}

//Kruskal: devuelve un arreglo con las aristas del árbol de expansión mínimo.
//Funciona para grafos no dirigidos y dirigidos: en los dirigidos cada arco se trata
//como arista sin dirección (el grafo no dirigido subyacente).
//Si el grafo no es conexo, devuelve un bosque de expansión mínimo (menos de n-1 aristas).
Arco * kruskal(Graph * grafo, int * cant){
    *cant = 0;
    if(grafo == NULL)
        return NULL;

    Stack * vertices = recolectar(grafo);
    if(vertices == NULL)
        return NULL;
    int n = vertices->cant;
    if(n == 0){
        Stack_free(vertices);
        return NULL;
    }

    //Cada arista aparece en ambos extremos si el grafo es no dirigido; el orden de Kruskal descarta la copia repetida
    int m = 0;
    for(int i = 0; i < n; i++)
        m += vertices->datos[i]->nexo;

    Arco * aristas = malloc(sizeof(Arco) * (m > 0 ? m : 1));
    int * padre = malloc(sizeof(int) * n);
    Arco * mst = malloc(sizeof(Arco) * (n > 1 ? n - 1 : 1));
    if(aristas == NULL || padre == NULL || mst == NULL){
        printf("\n No se pudo reservar memoria para el MST");
        free(aristas);
        free(padre);
        free(mst);
        Stack_free(vertices);
        return NULL;
    }

    int k = 0;
    for(int i = 0; i < n; i++){
        Vertice * u = vertices->datos[i];
        for(int j = 0; j < u->nexo; j++){
            aristas[k].origen = u;
            aristas[k].destino = u->lista[j].destino;
            aristas[k].peso = u->lista[j].peso;
            k++;
        }
    }

    qsort(aristas, m, sizeof(Arco), cmp_peso);

    for(int i = 0; i < n; i++)
        padre[i] = i;

    int total = 0;
    for(int e = 0; e < m && total < n - 1; e++){
        int a = buscar(padre, indice(vertices, aristas[e].origen));
        int b = buscar(padre, indice(vertices, aristas[e].destino));
        if(a != b){                 //No cierra ciclo: se incluye
            padre[a] = b;
            mst[total++] = aristas[e];
        }
    }

    free(aristas);
    free(padre);
    Stack_free(vertices);

    *cant = total;
    return mst;
}
