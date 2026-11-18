#include "Header.h"

//Busca un vértice por dato entre los registrados; si no existe, lo crea y lo registra
static Vertice * buscarOCrear(Graph * grafo, int dato){
    for(int i = 0; i < grafo->vertices->cant; i++)
        if(grafo->vertices->datos[i]->dato == dato)
            return grafo->vertices->datos[i];

    Vertice * nuevo = crearVertice(dato);
    if(nuevo == NULL)
        return NULL;
    push(grafo->vertices, nuevo);
    if(grafo->nodos == NULL)
        grafo->nodos = nuevo;   //El primer vértice leído es el inicio del recorrido
    return nuevo;
}

//Agrega el arco origen->destino con su peso
static int agregarArco(Vertice * origen, Vertice * destino, int peso){
    Arista * tmp = realloc(origen->lista, (origen->nexo + 1) * sizeof(Arista));
    if(tmp == NULL)
        return 0;
    origen->lista = tmp;
    origen->lista[origen->nexo].destino = destino;
    origen->lista[origen->nexo].peso = peso;
    origen->nexo++;
    return 1;
}

//Lee un grafo desde archivo (formato en Grafo1.txt). Devuelve NULL si hay error.
//*dirigido queda en 1 si el grafo es dirigido y en 0 si no lo es.
Graph * leerGrafo(const char * ruta, int * dirigido){
    FILE * f = fopen(ruta, "r");
    if(f == NULL){
        printf("\n No se pudo abrir el archivo %s", ruta);
        return NULL;
    }

    Graph * grafo = Graph_init();
    char linea[256];
    int encabezado = 0;     //Ya se leyó la primera línea con tipo y cantidad
    int m = 0;              //Cantidad de aristas declarada
    int leidas = 0;         //Cantidad de aristas leídas

    while(fgets(linea, sizeof linea, f) != NULL){
        if(linea[0] == '#')
            continue;

        if(!encabezado){
            if(sscanf(linea, "%d %d", dirigido, &m) != 2 || (*dirigido != 0 && *dirigido != 1)){
                printf("\n Encabezado inválido en %s (se espera: tipo cantidad_aristas)", ruta);
                break;
            }
            encabezado = 1;
            continue;
        }

        int origen, destino, peso;
        int campos = sscanf(linea, "%d %d %d", &origen, &destino, &peso);
        if(campos == EOF)
            continue;           //Línea vacía
        if(campos != 3){
            printf("\n Arista inválida en %s: %s", ruta, linea);
            break;
        }

        Vertice * u = buscarOCrear(grafo, origen);
        Vertice * v = buscarOCrear(grafo, destino);
        if(u == NULL || v == NULL || !agregarArco(u, v, peso)){
            printf("\n No se pudo agregar la arista %d %d", origen, destino);
            break;
        }
        //En un grafo no dirigido la arista va en ambos sentidos
        if(!*dirigido && !agregarArco(v, u, peso)){
            printf("\n No se pudo agregar la arista %d %d", destino, origen);
            break;
        }
        leidas++;
    }

    fclose(f);

    if(!encabezado || leidas != m){
        printf("\n El archivo %s no tiene las %d aristas declaradas (se leyeron %d)", ruta, m, leidas);
        liberarGrafo(grafo);
        return NULL;
    }

    grafo->grado = grafo->vertices->cant;
    return grafo;
}
