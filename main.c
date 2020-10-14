/** Pancakes

    Comparación de algoritmos búsqueda.

    Miguel Ángel Norzagaray Cosío
    20170831 (llegando la tormenta tropical Lidia)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PROF 	9
#define TAM 		8

#include "Pancakes.h"

int main()
{
	int i;
	int DesordenInicial = 20;
	char Pancakes[64], PancakesOriginal[64];


	/* Globales */
	INFINITO = 1.0/0.0;
	ENCONTRADO = 1.0;
	MaxProf = MAX_PROF;
	TamSolucion=0;
	TamMejorSolucion=MAX;
	Tam = TAM;
	H = h4;
	strcpy(Objetivo,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPARSTUVWXYZ");
	strncpy(Pancakes,Objetivo,Tam);
	Pancakes[Tam] = '\0';

	puts("\nPancakes - para inteligencia artificial I\n");
	puts("Desordenando ...");
	Desordenar(Pancakes,DesordenInicial);
	printf(": %s\n",Pancakes);
	strcpy(PancakesOriginal,Pancakes);

	/** Estableciendo un desorden específico
	strcpy(Pancakes,"badc");
	strcpy(PancakesOriginal,Pancakes);
	MaxProf = 4;
	Tam = 4;
	printf(": %s\n",Pancakes); */

	puts("\nAlgoritmo\t\t\tNodos\tSolución");

	{/** Búsqueda en profundidad */
	printf("\nBúsqueda en profundidad\t\t");
	Nodos = 0;
	BusqProf(Pancakes,0);
	printf("%ld\t",Nodos);
	for ( i=0; i<TamMejorSolucion ; i++ )
		printf("%d ",MejorSolucion[i]);}

	{/** Búsqueda actualizando la profundidad máxima */
	strcpy(Pancakes,PancakesOriginal);
	printf("\nActualizando la profundidad\t");
	MaxProf = MAX_PROF;
	TamSolucion=0;
	TamMejorSolucion=MAX;
	Nodos = 0;
	BusqProfAct(Pancakes,0);
	printf("%ld\t",Nodos);
	for ( i=0; i<TamMejorSolucion ; i++ )
		printf("%d ",MejorSolucion[i]);}

	{/** Búsqueda con profundidad iterativa */
	strcpy(Pancakes,PancakesOriginal);
	printf("\nProfundidad iterativa\t\t");
	MaxProf = MAX_PROF;
	TamSolucion=0;
	TamMejorSolucion=MAX;
	Nodos = 0;
	BusqProfIterativa(Pancakes,0);
	printf("%ld\t",Nodos);
	for ( i=0; i<TamMejorSolucion ; i++ )
		printf("%d ",MejorSolucion[i]);}

	{/** Búsqueda en amplitud */
	strcpy(Pancakes,PancakesOriginal);
	printf("\nEn amplitud\t\t\t");
	MaxProf = MAX_PROF;
	TamSolucion=0;
	TamMejorSolucion=MAX;
	Nodos = 0;
	BusqAmpli(Pancakes);
	printf("%ld\t",Nodos);
	for ( i=0; i<TamMejorSolucion ; i++ )
		printf("%d ",MejorSolucion[i]);}

	{/** Búsqueda AStar */
	strcpy(Pancakes,PancakesOriginal);
	printf("\nAlgoritmo A*\t\t\t");
	MaxProf = MAX_PROF;
	TamSolucion=0;
	TamMejorSolucion=MAX;
	Nodos = 0;
	AStar(Pancakes);
	printf("%ld\t",Nodos);
	for ( i=0; i<TamMejorSolucion ; i++ )
		printf("%d ",MejorSolucion[i]);}

	{/** Búsqueda IDA */
	strcpy(Pancakes,PancakesOriginal);
	printf("\nAlgoritmo IDA\t\t\t");
	MaxProf = MAX_PROF;
	TamSolucion=0;
	TamMejorSolucion=MAX;
	Nodos = 0;
	IDA(Pancakes);
	printf("%ld\t",Nodos);
	for ( i=0; i<TamMejorSolucion ; i++ )
		printf("%d ",MejorSolucion[i]);}

	printf("\n\nFin de programa.\n");

	return 0;
}

void Desordenar(char *s, int n)
{
	int i,i_ant;
	int L = strlen(s)-1;
	time_t t;

	srand((unsigned) time(&t));

	i_ant = 0;
	for ( ; n>0 ; n--) {
		i = rand()%L + 2;
		if ( i == i_ant ) {
			n++;
			continue;
		}
		printf("%d ",i);
		Voltear(s,i);
		i_ant = i;
	}
}

void Voltear(char *s, int n)
{
	char c;
	int i,j,L;

	if ( n < 2 )
		return;
	L = strlen(s);
	if ( n>L )
		return;

	for ( i = L-n, j = L-1 ; i<j ; i++,j-- ) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/* Fin de archivo */
