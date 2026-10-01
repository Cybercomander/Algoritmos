#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Usuario.h"
#include "Merge.h"

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

int main(int argc, char *argv[]) {
    // Obtener la ruta del archivo de usuarios
    const char *archivo = (argc > 1) ? argv[1] : ARCHIVO_DEFAULT;

    // Crear la lista y cargar los usuarios
    Lista *lista = crear_lista();
    if (!cargar_usuarios(archivo, lista) || lista->longitud == 0) {
        printf("\n No hay usuarios para analizar. Saliendo del programa...\n");
        liberar_lista(lista);
        return 1;
    }

    // Mostrar el menu principal
    menu(lista);

    // Liberar la memoria de la lista
    liberar_lista(lista);

    return 0;
}

// Funcion para inicializar una lista vacia
Lista* crear_lista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (lista == NULL) {
        printf("\nError al asignar memoria para la lista");
        exit(EXIT_FAILURE);
    }
    lista->cabeza = NULL;
    lista->cola = NULL;
    lista->longitud = 0;
    return lista;
}

// Funcion para crear un nuevo usuario
User* crear_usuario(int id, const char *nombre, int grado) {
    User* nuevo = (User*)calloc(1, sizeof(User));
    if (nuevo == NULL) {
        printf("\nError al asignar memoria para el usuario");
        exit(EXIT_FAILURE);
    }
    nuevo->id = id;
    strncpy(nuevo->nombre, nombre, MAX_NOMBRE - 1);
    nuevo->nombre[MAX_NOMBRE - 1] = '\0';
    nuevo->grado = grado;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    return nuevo;
}

// Funcion para insertar un usuario al final de la lista
void insertar_usuario(Lista *lista, User *usuario) {
    if (lista->cabeza == NULL) {
        lista->cabeza = usuario;
        lista->cola = usuario;
    } else {
        lista->cola->siguiente = usuario;
        usuario->anterior = lista->cola;
        lista->cola = usuario;
    }
    lista->longitud++;
}

// Funcion para liberar una lista
void liberar_lista(Lista *lista) {
    if (lista == NULL) {
        return;
    }

    User *actual = lista->cabeza;
    User *siguiente;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    free(lista);
}

// Funcion para cargar los usuarios desde un archivo de texto (solo lectura)
int cargar_usuarios(const char *archivo, Lista *lista) {
    FILE *fp = fopen(archivo, "r");
    if (fp == NULL) {
        printf("\n No se pudo abrir el archivo '%s'.", archivo);
        return 0;
    }

    char linea[MAX_LINEA];
    char nombre[MAX_NOMBRE];
    int grado;
    int contador = 0;
    int num_linea = 0;

    while (fgets(linea, MAX_LINEA, fp) != NULL) {
        num_linea++;

        // Separar la linea en nombre y grado (formato: nombre;grado)
        sscanf(linea, "%254[^;];%d", nombre, &grado);

        insertar_usuario(lista, crear_usuario(++contador, nombre, grado));
    }

    fclose(fp);

    printf("\n Archivo '%s' cargado.", archivo);
    printf("\n Usuarios cargados: %d", contador);
    return 1;
}

// Funcion para imprimir un usuario
void imprimir(User usuario) {
    printf("%-4d | ", usuario.id);
    printf("%-30s | ", usuario.nombre);
    printf("%5d", usuario.grado);
}

// Funcion para mostrar el encabezado del resultado
void mostrar_encabezado() {
    printf("\n %-4s | %-30s | %5s", "ID", "NOMBRE", "GRADO");
    printf("\n------------------------------------------------");
}

// Funcion para imprimir la lista de usuarios
void imprimir_lista_usuarios(Lista *lista) {
    if (lista == NULL || lista->longitud == 0) {
        printf("\n No hay usuarios en la lista.");
        return;
    }

    mostrar_encabezado();

    User *actual = lista->cabeza;
    while (actual != NULL) {
        printf("\n ");
        imprimir(*actual);
        actual = actual->siguiente;
    }

    printf("\n\n Total de usuarios: %d", lista->longitud);
}

// Funcion para limpiar el buffer de entrada
void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Menu principal
void menu(Lista *lista) {
    int opcion = 0;

    while (opcion != 4) {
        printf("\n\n");
        printf("\n======================================================");
        printf("\n          ANALIZADOR DE REDES SOCIALES (DEMO)         ");
        printf("\n======================================================");
        printf("\n 1. Mostrar lista de usuarios");
        printf("\n 2. Ordenar por GRADO - Ascendente");
        printf("\n 3. Ordenar por GRADO - Descendente");
        printf("\n 4. Salir");
        printf("\n------------------------------------------------------");
        printf("\n Ingrese una opcion: ");
        opcion = 0;
        scanf("%d", &opcion);
        limpiar_buffer();

        switch (opcion) {
            case 1:
                mergeSort(lista, POR_ID, ASCENDENTE);
                printf("\n Lista de usuarios:");
                imprimir_lista_usuarios(lista);
                break;
            case 2:
                mergeSort(lista, POR_GRADO, ASCENDENTE);
                printf("\n Usuarios ordenados por grado (ascendente):");
                imprimir_lista_usuarios(lista);
                break;
            case 3:
                mergeSort(lista, POR_GRADO, DESCENDENTE);
                printf("\n Usuarios ordenados por grado (descendente):");
                imprimir_lista_usuarios(lista);
                break;
            case 4:
                printf("\n Saliendo del programa...\n");
                break;
            default:
                printf("\n Opcion no valida. Intente nuevamente.");
        }
    }
}