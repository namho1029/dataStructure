#include <stdio.h>
#include <stdlib.h>

int main()
{
    double* p1;
    p1 = (double*)malloc(sizeof(double)); 
    *p1 = 23.92;  

    return 0;
}
