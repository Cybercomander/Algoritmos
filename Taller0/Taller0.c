#include <stdio.h>
int main (void)
{
    char caracter = 'A';
    char* texto="Omar";
    int entero = 10;
    float flotante = 1.5543;
    double doble = 0.000008;
    printf("Hol%c %s\n",caracter,texto);
    printf("entero=%d\n",entero);
    printf("flotante=%f\n",flotante);
    printf("doble=%lf\n",doble);
    return 0;
}