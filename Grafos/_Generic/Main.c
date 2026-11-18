#include "Header.h"

int main(void){

    srand(time(NULL));

    double random = (rand() % (10 - 1 + 1 ) + 1);
    printf("%lf", random);

    return 1;
}