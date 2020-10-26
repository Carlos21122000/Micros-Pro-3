/*--------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* CC3056-10 Programación de microprocesadores
* Autores: Juan Marroquin y Carlos Raxtum

* --------------------------------------------------------*/
//librerias que usaremos 
#include <omp.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <ctime>

#define n 250

int main()
{
	//Informacion de lo que va a hacer le programa
	printf("Programa para resolver la serie de  1/(n*(n+1)) , desde 1 hasta infinito \n");
	
	//variables para convergencia
	double converge= 0;
	int convergeInt = 0;
	double converge2 = 0;
	int convergeInt2 = 0;
	int valorLim = 0;
	
	//valor con limites
	for(int i = 1; i < 10000; i+=1000)
	{
		//se utiliza la ecuacion obtenida con limites
		double num = i/(i+2.f);	
		//se muestran los cambios en cada corrida del limite
		printf("Con i = %d Valor limite es  => %lf \n", i, num);
	}
	
	//parte paralela para obtener las sumatorias
	#pragma omp parallel for num_threads(n)
		for(int i =1; i<598461; i++)
		{
			//cada hilo realiza la operacion dada
			double val= 1.f/(i*(i+1.f));
			
			//cada hilo almacena el dato en la variable convergencia
			#pragma omp atomic 
				converge+=val; 
		}	
	
	
		
	//parte paralela para obtener las sumatoria con otra n
	#pragma omp parallel for num_threads(n)
		for(int i =1; i<710000; i++)
		{
			//cada hilo realiza la operacion dada
			double val2 = 1.f/(i*(i+1.f));
			
			//cada hilo almacena el dato en la variable convergencia
			#pragma omp atomic 
				converge2+=val2; 
		}	
	
	//se redondea la la sumatoria 
	convergeInt = round(converge);
	convergeInt2 = round(converge2);
	//Se muestran los valores originales y redondeados
	printf("El valor de convergencia aproximado con n= 598461 es: %lf \n", converge);
	printf("El valor de convergencia aproximado con n= 710000 es: %lf \n", converge2);
	printf("El valor de convergencia entero es: %d \n", convergeInt);
	
	return 0;
}
