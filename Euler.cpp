/*--------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* CC3056-10 Programación de microprocesadores
* Autores: Juan Marroquin y Carlos Raxtum

* --------------------------------------------------------*/
//librerias que usaremos 
#include <omp.h>                         
#include <stdio.h>
#include <stdlib.h>

// funcion que calcula el factorial de un nimero
float fact(int n) {
	if (n < 0)
		return -1; // en caso que el numero sea menor que 0, regresa un -1
	else if (n == 0)
		return 1; // condicion que realiza el factorial de 0
	else
		return n * fact(n - 1); // condicion que realiza el factorial de un numero
}
int main() {
	int n; //Valor para el ciclo for de open mp
	float e = 0; // variable para almacenar el valor de e 
	printf("Ingrese un valor, mientras mas grande sea el valor, mayor exactitud tendra el resultado\n");
	scanf("%d", &n);
	//pragma omp for para paralelizar y agilizar el resultado
	#pragma omp parallel for
	for (int i = 0; i < n; i++)
		#pragma omp atomic
			e += (1 / fact(i));

	printf("\nEl valor de Euler es: %f\n", e);
}
