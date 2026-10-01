#ifndef MAIN_H
#define MAIN_H

    #include "Usuario.h"

    //DEFINES
    #define MAX_LINEA 300
    #define ARCHIVO_DEFAULT "usuarios.txt"

    // PROTOTIPOS PARA MANEJO DE LISTAS
    Lista* crear_lista();
    User* crear_usuario(int id, const char *nombre, int grado);
    void insertar_usuario(Lista *lista, User *usuario);
    void liberar_lista(Lista *lista);

    // PROTOTIPOS PARA CARGA DE DATOS
    int cargar_usuarios(const char *archivo, Lista *lista);

    // PROTOTIPOS PARA IMPRESION
    void imprimir(User usuario);
    void mostrar_encabezado();
    void imprimir_lista_usuarios(Lista *lista);

    // PROTOTIPOS PARA LOS MENUS
    void limpiar_buffer();
    void menu(Lista *lista);

#endif
