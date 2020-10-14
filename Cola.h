/** Cola.h */

#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#include "Pancakes.h"

struct Nodo {
	int n;
	int Prof;
	int Priori;	/* La distancia global */
	struct Nodo *sig;
	struct Nodo *p;		// Nodo padre
	char s[MAX];
};

typedef struct {
	struct Nodo *Ini;
	struct Nodo *Fin;
	int Cont;
} Cola;

void SetUpCola(Cola *C);
int ColaVacia(Cola *C);
int AgregarCola(Cola *C, int n, int Prof, struct Nodo *P, char *s);
int AgregarColaPriori(Cola *C, int n, int Prof, int Priori,
		struct Nodo *p, char *s);
struct Nodo *SacarCola(Cola *C);

#endif // COLA_H_INCLUDED

/* Fin de archivo */
