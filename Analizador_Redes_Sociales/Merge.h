#ifndef MERGE_H
#define MERGE_H

    #include "Usuario.h"

    // PROTOTIPOS PARA EL MERGE SORT SOBRE LA LISTA DE USUARIOS
    void mergeSort(Lista *lista, Criterio criterio, Orden orden);
    void merge(Lista *lista, int izq, int med, int der, Criterio criterio, Orden orden);
    User* obtener_usuario(Lista *lista, int posicion);
    int comparar(User *a, User *b, Criterio criterio, Orden orden);

#endif
