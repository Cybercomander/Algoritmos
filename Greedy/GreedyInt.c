#include "Greedy.h"

int main(int argc, char * argv[]){

    int A[5]={5,5,6,6,5}, B[5]={1,2,5,4,3}, K=5;
    int C[4]={2,2,4,3}, D[4]={2,4,2,3}, L=0;
    int E[4]={1,2,2,1}, F[4]={4,4,5,4}, M=4;

    printf( "\n\t\t ||=================================||"
            "\n\t\t ||      Arreglos originales        ||"
            "\n\t\t ||=================================||");
    
    printf("\n\nArreglo A = ");
    imprimir(A, (sizeof(A) / sizeof(A[0])));
    printf("\tArreglo B = ");
    imprimir(B, (sizeof(B) / sizeof(B[0])));
    printf("\nArreglo C = ");
    imprimir(C, (sizeof(C) / sizeof(C[0])));
    printf("\t\tArreglo D = ");
    imprimir(D, (sizeof(D) / sizeof(D[0])));
    printf("\nArreglo E = ");
    imprimir(E, (sizeof(E) / sizeof(E[0])));
    printf("\t\tArreglo F = ");
    imprimir(F, (sizeof(F) / sizeof(F[0])));

    // APLICAR ALGORITMO A LOS ARREGLOS
    greedy(A, (sizeof(A) / sizeof(A[0])), B, (sizeof(B) / sizeof(B[0])), K);
    greedy(C, (sizeof(C) / sizeof(C[0])), D, (sizeof(D) / sizeof(D[0])), L);
    greedy(E, (sizeof(E) / sizeof(E[0])), F, (sizeof(F) / sizeof(F[0])), M);

    printf( "\n\n\t\t ||=================================||"
            "\n\t\t ||      Arreglos post greedy       ||"
            "\n\t\t ||=================================||");
    
    printf("\n\nArreglo A = ");
    imprimir(A, (sizeof(A) / sizeof(A[0])));
    printf("\tArreglo B = ");
    imprimir(B, (sizeof(B) / sizeof(B[0])));
    printf("\nArreglo C = ");
    imprimir(C, (sizeof(C) / sizeof(C[0])));
    printf("\t\tArreglo D = ");
    imprimir(D, (sizeof(D) / sizeof(D[0])));
    printf("\nArreglo E = ");
    imprimir(E, (sizeof(E) / sizeof(E[0])));
    printf("\t\tArreglo F = ");
    imprimir(F, (sizeof(F) / sizeof(F[0])));

    printf("\n\nSumatoria del arreglo A = %d", sumArr(A, (sizeof(A) / sizeof(A[0]))));
    printf("\nSumatoria del arreglo C = %d", sumArr(C, (sizeof(C) / sizeof(C[0]))));
    printf("\nSumatoria del arreglo E = %d", sumArr(E, (sizeof(E) / sizeof(E[0]))));


    return 0;
}

void greedy(int A[], int sizeA, int B[], int sizeB, int k){
    while (k!=0){
        int tmp = A[0];
        int posi = 0;
        for (int i = 0 ; i < sizeA; i++)
            if (A[i] < tmp){
                tmp = A[i];
                posi = i;
            }
        

        int tmpp = B[0];
        int posii = 0;
        for (int j = 0; j < sizeB; j++)
            if (B[j] > tmpp){
                tmpp = B[j];
                posii = j;
            }
        

        if (tmp < tmpp)
            swap(A, posi, B, posii);
            k--;
    }
}

    
    void swap(int A[],int posi, int B[], int posii){
        int tmp = A[posi];
        A[posi] = B[posii];
        B[posii] = tmp;
    }

    void imprimir(int arr[], int size){

        printf("[ %d", arr[0]);
        for (int i = 1 ; i < size ; i++)
            printf (", %d", arr[i]);
        printf(" ]");

    }

    int sumArr(int arr[], int size){

        int suma = 0;
        for(int i = 0 ; i < size ; i++)
            suma+= arr[i];

        return suma;
    }