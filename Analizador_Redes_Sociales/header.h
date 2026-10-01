#ifndef HEADER_H
#define HEADER_H

    #include <stdio.h>
    #include <math.h>
    #include <stdlib.h>
    #include "Pila.h"
    #include "Merge.h"

    typedef struct User{
        char nombre[255];
        int id;
        int grado;
        User * next;
        User * anterior;
    }User;

#endif