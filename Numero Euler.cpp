#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Formula usada: (1+(1/n))^n

int main()
{
    printf("  **  CALCULO DEL NUMERO DE EULER (NUMERO 'e')  **\n\n");
    double a, b, c, LIMIT=9999999999;
    system("  PAUSE");
    a = pow(1+(1/LIMIT),LIMIT);
    printf("\n\n  El numero es %lf", a);
    return 0;
}