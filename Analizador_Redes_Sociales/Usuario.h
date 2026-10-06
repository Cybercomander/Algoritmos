#ifndef USUARIO_H
#define USUARIO_H

//DEFINES
    #define MAX_NOMBRE 255

    //ESTRUCTURA DE USUARIO (NODO DE LA LISTA DOBLEMENTE ENLAZADA)
    typedef struct User{
        char nombre[MAX_NOMBRE];
        int id;
        int grado;
        struct User *siguiente;
        struct User *anterior;
    }User;

    //ESTRUCTURA DE LISTA DE USUARIOS
    typedef struct Lista{
        User *cabeza;
        User *cola;
        int longitud;
    }Lista;

    //CRITERIOS DE ORDENAMIENTO
    typedef enum{
        POR_ID,
        POR_GRADO
    }Criterio;

    //SENTIDO DEL ORDENAMIENTO
    typedef enum{
        ASCENDENTE,
        DESCENDENTE
    }Orden;

#endif
