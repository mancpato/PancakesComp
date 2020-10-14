/** Cola.c */

#include <stdlib.h>
#include <string.h>
#include "Cola.h"

void SetUpCola(Cola *C)
{
	C->Ini = C->Fin = NULL;
	C->Cont=0;
}

int ColaVacia(Cola *C)
{
	if ( C->Cont==0 )
		return 1;
	return 0;
}

int AgregarCola(Cola *C, int n, int Prof, struct Nodo *P, char *s)
{
	struct Nodo *R;

	if ( !(R=(struct Nodo *)malloc(sizeof(struct Nodo))) ) {
		return 0;
	}

	R->n = n;
	R->Prof = Prof;
	R->p = P;
	strcpy(R->s, s);
	C->Cont++;

	if ( !C->Ini )
		C->Ini = C->Fin = R;
	else
		C->Fin->sig = R;
	R->sig = NULL;
	C->Fin = R;

	return 1;
}

int AgregarColaPriori(Cola *C, int n, int Prof, int Priori,
		struct Nodo *P, char *s)
{
	struct Nodo *R, *t, *ta;

	if ( !(R=(struct Nodo *)malloc(sizeof(struct Nodo))) ) {
		return 0;
	}

	R->n = n;
	R->Prof = Prof;
	R->Priori = Priori;
	R->p = P;
	strcpy(R->s, s);
	C->Cont++;

	if ( !C->Ini ) {
		C->Ini = C->Fin = R;
		R->sig = NULL;
	} else if ( Priori < C->Ini->Priori ) {
		R->sig = C->Ini;
		C->Ini = R;
	} else {
		ta = C-> Ini;
		t = ta->sig;
		while ( t ) {
			if ( Priori < t->Priori )
				break;
			ta = t;
			t = t->sig;
		}
		R->sig = t;
		ta->sig = R;
		if ( !t )
			C->Fin = R;
	}

	return 1;
}

struct Nodo *SacarCola(Cola *C)
{
	struct Nodo *R;

	R = C->Ini;
	C->Ini = C->Ini->sig;
	C->Cont--;
	return R;
};

/* Fin de archivo */
