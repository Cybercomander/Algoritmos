#include "Header.h"

//Devuelve 1 si el nodo ya está en la pila de visitados, 0 si no
int visitado(Stack * visitados, Vertice * nodo){
    for(int i = 0; i < visitados->cant; i++)
        if(visitados->datos[i] == nodo)
            return 1;
    return 0;
}

//Recorrido en profundidad desde grafo->nodos; devuelve el vértice con dato, o NULL si no existe
Vertice * dfs(Graph * grafo, int dato){
    if(grafo == NULL || grafo->nodos == NULL)
        return NULL;

    Stack * pila = Stack_init();        //Nodos pendientes por explorar
    Stack * visitados = Stack_init();   //Nodos ya explorados
    if(pila == NULL || visitados == NULL){
        Stack_free(pila);
        Stack_free(visitados);
        return NULL;
    }

    Vertice * encontrado = NULL;
    push(pila, grafo->nodos);

    while(Stack_void(pila)){
        Vertice * nodo = pop(pila);
        if(visitado(visitados, nodo))   //Pudo entrar varias veces a la pila
            continue;
        push(visitados, nodo);

        if(nodo->dato == dato){
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
