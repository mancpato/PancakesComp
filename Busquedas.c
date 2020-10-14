/***
Algoritmos de búsqueda.

Programa de ejemplo del problema de los pancakes para IA I.

	BusqProf		Búsqueda en profundidad normal.
	BusqProfAct		Búsqueda en profundidad, actualizando la
				profundidad máxima.
	BusqProfIterativa	Búsqueda en profundidad creciente.
	BusqAmpli		Búsqueda en amplitud normal.
	AStar			Busqueda en amplitud con cola de prioridad.
	IDA			Iterative Deepening A*

Miguel Ángel Norzagaray Cosío
20170912
*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>

#include "Pancakes.h"
#include "Cola.h"

/** BusqProf
	Búsqueda en profundidad normal.

    s:		Cadena que representa los pancakes
    n_ant:	La cantidad de pancakes recien volteados

*/
void BusqProf(char *s, int n_ant)
{
	Nodos++;

	if ( !strncmp(s,Objetivo,Tam) ) {
		if ( TamSolucion < TamMejorSolucion ) {
			for ( int i = 0; i < TamSolucion ; i++ )
				MejorSolucion[i] = SolucionActual[i];
			TamMejorSolucion = TamSolucion;
		}
		return;
	}
	if ( MaxProf <= TamSolucion )
		return;

	for ( int i = 2 ; i <= Tam ; i++ ) {
		if ( i == n_ant )
			continue;
		Voltear(s,i);
		SolucionActual[TamSolucion++] = i;
		BusqProf(s,i);
		Voltear(s,i);
		TamSolucion--;
	}
}

/** BusqProfAct
	Búsqueda en profundidad, actualizando la profundidad máxima.

    s:		Cadena que representa los pancakes
    n_ant:	La cantidad de pancakes recien volteados
*/
void BusqProfAct(char *s, int n_ant)
{
	int i;

	Nodos++;

	if ( !strncmp(s,Objetivo,Tam) ) {
		if ( TamSolucion < TamMejorSolucion ) {
			for ( i = 0; i < TamSolucion ; i++ )
				MejorSolucion[i] = SolucionActual[i];
			TamMejorSolucion = TamSolucion;
			MaxProf = TamMejorSolucion;
		}
		return;
	}
	if ( MaxProf <= TamSolucion )
		return;

	for ( i = 2 ; i <= Tam ; i++ ) {
		if ( i == n_ant )
			continue;
		Voltear(s,i);
		SolucionActual[TamSolucion++] = i;
		BusqProfAct(s,i);
		Voltear(s,i);
		TamSolucion--;
	}
}

/** BusqProfIterativa
	Búsqueda en profundidad creciente.

    s:		Cadena que representa los pancakes
    n_ant:	La cantidad de pancakes recien volteados

*/
void BusqProfIterativa(char* s, int n_ant)
{
	int BusqProfIt(char *s, int n_ant);

	SolucionEncontrada = 0;
	for ( MaxProf=1 ; !SolucionEncontrada ; MaxProf++ ) {
		TamSolucion=0;
		TamMejorSolucion=MAX;
		if ( BusqProfIt(s, 0) )
			break;
	}
}

/** BusqProfIt
	Búsqueda en profundidad normal.

    s:		Cadena que representa los pancakes
    n_ant:	La cantidad de pancakes recien volteados

*/
int BusqProfIt(char *s, int n_ant)
{
	int i;

	Nodos++;

	if ( !strncmp(s,Objetivo,Tam) ) {
		SolucionEncontrada = 1;
		if ( TamSolucion < TamMejorSolucion ) {
			for ( i = 0; i < TamSolucion ; i++ )
				MejorSolucion[i] = SolucionActual[i];
			TamMejorSolucion = TamSolucion;
			MaxProf = TamSolucion - 1;
		}
		return 1;
	}
	if ( MaxProf <= TamSolucion )
		return 0;

	for ( i = 2 ; i <= Tam ; i++ ) {
		if ( i == n_ant )
			continue;
		Voltear(s,i);
		SolucionActual[TamSolucion++] = i;
		if ( BusqProfIt(s,i) ) {
			Voltear(s,i);
			return 1;
		}
		Voltear(s,i);
		TamSolucion--;
	}
	return 0;
}

/** BusqAmpli
	Búsqueda en amplitud normal.

    s:		Cadena que representa los pancakes
*/
void BusqAmpli(char *s)
{
	int i, n_ant=0;
	char Cad[MAX];
	Cola C;
	struct Nodo *R;

	if ( !strncmp(Cad,Objetivo,Tam) )
		return;
	SetUpCola(&C);
	Nodos = 1;
	AgregarCola(&C, 0, 0, NULL, s);
	Nodos = 1;
	while ( !ColaVacia(&C) ) {
		R = SacarCola(&C);
		strcpy(Cad,R->s);
		n_ant = R->n;
		for ( i = 2 ; i <= Tam ; i++ ) {
			if ( i == n_ant )
				continue;
			Voltear(Cad,i);
			if ( !strncmp(Cad,Objetivo,Tam) )
				goto SOLUCION;
			AgregarCola(&C, i, R->Prof+1,R,Cad);
			Voltear(Cad,i);
			Nodos++;
		}
	}

SOLUCION:
	TamMejorSolucion = R->Prof+1;
	MejorSolucion[R->Prof] = i;
	while ( R->p ) {
		MejorSolucion[R->Prof-1]=R->n;
		R = R->p;
	}
}

/** AStar

	Busqueda en amplitud con cola de prioridad.
*/
void AStar(char *s)
{
	int i, h, n_ant=0;
	char Cad[MAX];
	Cola C;
	struct Nodo *R;

	if ( !strncmp(Cad,Objetivo,Tam) )
		return;
	SetUpCola(&C);
	Nodos = 1;
	AgregarColaPriori(&C, 0, 0, 0, NULL, s);
	while ( !ColaVacia(&C) ) {
		R = SacarCola(&C);
		strcpy(Cad,R->s);
		n_ant = R->n;
		for ( i = 2 ; i <= Tam ; i++ ) {
			if ( i == n_ant )
				continue;
			Voltear(Cad,i);
			if ( !strncmp(Cad,Objetivo,Tam) )
				goto SOLUCION;
			h = R->Prof + H(Cad);
			AgregarColaPriori(&C, i, R->Prof+1,h,R,Cad);
			Voltear(Cad,i);
			Nodos++;
		}
	}
SOLUCION:
	TamMejorSolucion = R->Prof+1;
	MejorSolucion[R->Prof] = i;
	while ( R->p ) {
		MejorSolucion[R->Prof-1]=R->n;
		R = R->p;
	}
}

/** IDA

	Iterative Deepening A*.
*/
float IDA(char *s)
{
	int Cota, i;
	float t;
	float Busq_IDA(char *s, int ant, int Cota);

	Cota = H(s);
	do {
		t = Busq_IDA(s, 0, Cota);
		if ( t == ENCONTRADO ) {
			TamMejorSolucion = TamSolucion;
			for ( i = 0; i < TamSolucion ; i++ )
				MejorSolucion[i] = SolucionActual[i];
			return ENCONTRADO;
		}
		if ( t == INFINITO  ||  t == Cota )
			return INFINITO;
		Cota = t;
	} while ( 1 );
}

float Busq_IDA(char *s, int n_ant, int Cota)
{
	int i;
	float f, t, min;

	Nodos++;

	if ( !strncmp(s,Objetivo,Tam) )
		return 1;

	f = TamSolucion + H(s);

	if ( f > Cota )
		return f;

	min = INFINITO;
	for ( i = 2 ; i <= Tam ; i++ ) {
		if ( i == n_ant )
			continue;
		Voltear(s,i);
		SolucionActual[TamSolucion++] = i;
		t = Busq_IDA(s,i,Cota);
		if ( t == ENCONTRADO )
			return ENCONTRADO;
		if ( t<min )
			min = t;
		Voltear(s,i);
		TamSolucion--;
	}

	return min;
}

#ifdef __cplusplus
}
#endif

/* Fin de archivo */
