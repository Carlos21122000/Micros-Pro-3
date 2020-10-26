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
using namespace std;

/*
    funcion que calcula el factorial de un nimero
*/

float fact(int n) {
	if (n < 0)
		return -1; // en caso que el numero sea menor que 0, regresa un -1
	else if (n == 0)
		return 1; // condicion que realiza el factorial de 0
	else
		return n * fact(n - 1); // condicion que realiza el factorial de un numero
}
/*
    Calcular el numero de euler
*/
void euler1(){
    int s;//sumas para aproximación
    printf("Escriba un numero, recuerde que mientras mas grande es el valor,");
    printf("Mas exacto sera el resultado: ");
    scanf( "%d", &s );
    double e=0;
    #pragma omp parallel for
    for(int i=0;i<s;i++){
        double u=fact(i);
        #pragma omp atomic
        e+=1/u;//e+=1/fact(i)
    }
    cout<<"\nel valor aproximado de e en base a su numero "<<s<<" es "<<e<<endl;
}
/*
    El valor de convergencia de la serie (para n inicia en 1,)
*/
void seriesB(){
    //variables para convergencia
	double conv= 0;
	int valorLim = 0;
	int n = 0;
	
	printf( "Ingrese el numero al cual quiere obtener su valor de convergencia aproximado\n" );
    scanf( "\n   %d", &n );
	//parte paralela para obtener las sumatorias
	#pragma omp parallel for num_threads(n)
		for(int i =1; i<n; i++)
		{
			//cada hilo realiza la operacion dada
			double val= 1.f/(i*(i+1.f));
			
			//cada hilo almacena el dato en la variable convergencia
			#pragma omp atomic 
				conv+=val; 
		}	
	
	//Se muestran los valores originales y redondeados
	cout<<"El valor de convergencia aproximado con"<<n<<" es "<<conv<<"\n";
}
/*
    El valor de convergencia de la serie (para n inicia en 1)
*/
void serieC(){
    int hilos;
	double conv=0;
	double exp=0;
	double val=0;
	int n=0;

	//Se le permite al usuario especificar los hilos
	printf("Ingrese cantidad de hilos a usar (menor a 200)\n");
	scanf("%d",&hilos);
	
	
	while (hilos<200){
	    
	    //Limite cuando la serie tiende a infinito
	    exp = 1-(1/sqrt(n));
    	val = pow(round(exp),n);
    	printf("Valor del limite: %lf\n",val);
    	
    	if(val!=0){
	    	printf("Por el teorema la serie diverge\n");
	    }
    	else{
	    	printf("La serie es convergente\n");
	    }
	
	    printf( "Ingrese el numero al cual quiere obtener su valor de convergencia aproximado\n" );
        scanf( "\n   %d", &n );
	    //parte paralela para obtener las sumatorias
    	#pragma omp parallel for num_threads(hilos)
	    	for(int i =1; i<n; i++)
	    	{
		    	 val = pow(1-(1/sqrt(i)),i);
		    	#pragma omp atomic 
		    		conv+=val;	
	    	}
	
    	cout<<"El valor de convergencia aproximado con "<<n<<" es "<<conv<<"\n";
    	break;
    }   
}

int main()
{
    int n, opcion;

    do
    {
        printf( "\n   Bienvenidos a nuestro proyecto #3" );
        printf( "\n   1. El numero de euler" );
        printf( "\n   2. El valor de convergencia de la serie (para n inicia en 1,)" );
        printf( "\n   3. El valor de convergencia de la serie (para n inicia en 1)" );
        printf( "\n   4. Salir.\n" );

        scanf( "\n   %d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1: euler1();
                    break;

            case 2: seriesB();
                    break;

            case 3: serieC();
                    break;
         }

         /* Fin del anidamiento */

    } while ( opcion != 4 );

    return 0;
}
