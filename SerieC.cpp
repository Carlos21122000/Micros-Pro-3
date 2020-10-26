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

int main(){
	
	#define n 10000
	int hilos;
	double converge=0;
	double exp=0;
	double val=0;
	double converge2=0;
	double exp2=0;
	double val2=0;
	
	printf("Porgrama que calcula la serie de (1-1/raiz(n))^n, desde 1 hasta infinito\n");
	
	//Se le permite al usuario especificar los hilos
	printf("----------------------------------------------\n");
	printf("Ingrese cuantos hilos quiere usar: (menor a 200)\n");
	
	scanf("%d",&hilos);
	
	if(hilos>200){
		printf("Intente de nuevo.\n");
		return(1);
		}
		
	
	//Limite cuando la serie tiende a infinito
	printf("Teorema de la divergencia: \n");
	
	exp = 1-(1/sqrt(n));
	
	val = pow(round(exp),n);
	printf("Valor del limite: %lf\n",val);
	if(val!=0)
	{
		printf("Por el teorema la serie diverge\n");
	}
	else
	{
		printf("La serie es potencialmente convergente\n");
	}
	
	printf("EVALUANDO LA SERIE...........\n");
	
	//parte paralela para obtener las sumatorias
	#pragma omp parallel for num_threads(hilos)
		for(int i =1; i<700000; i++)
		{
			 val = pow(1-(1/sqrt(i)),i);
			
			#pragma omp atomic 
				converge+=val;	
		}
		
	#pragma omp parallel for num_threads(hilos)
		for(int i =1; i<710000; i++)
		{
			 val2 = pow(1-(1/sqrt(i)),i);
			
			#pragma omp atomic 
				converge2+=val2;		
		}	
	
	printf("El valor de la serie con n = 700,000 es: %lf \n", converge);
	printf("El valor de la serie con n = 710,000 es: %lf \n", converge2);
	
	if(converge2!=converge)
	{
		printf("La serie diverge\n");
	}
		
	else
	{
		printf("El valor de convergencia aproximado es: %lf \n", converge);
	}
	
	return 0;	
	
	}
