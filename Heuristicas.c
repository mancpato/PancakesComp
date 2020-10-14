/** Heurísticas.c

	Heurísticas para el programa de los pancakes.

	Los pancakes están representados por el abecedario en
    minúsculas: "abcdef  ... xyz".

*/

#include <stdlib.h>
#include <string.h>

/** h1

	Esta heurística cuenta cuántos panckaes están fuera de su posición.
EJEMPLO:
	acbegdihf    7
*/
int h1(char *s)
{
	int i, c;

	c=0;
	for ( i=0; s[i] ; i++ )
		if ( s[i] != 'a'+(char)i )
			c++;
	return c;
}

/** h2

	Esta heurística es la suma de las distancias de cada letra
    a la posición que le toca. NO ES ADMISIBLE, es decir, sobre estima
    el costo de resolver.
EJEMPLO:
	acbegdihf    12
*/
int h2(char *s)
{
	int i, c;

	c=0;
	for ( i=0; s[i] ; i++ )
		 c += abs((s[i]-'a') - i);
	return c;
}

/** h3

	Esta heurística regresa el menor pancake que está fuera de
    su posición.
EJEMPLO:
	acbegdihf    8
*/
int h3(char *s)
{
	int i;

	for ( i=0; s[i] ; i++ )
		 if ( s[i] != (char)('a'+i) )
			break;
	return strlen(s)-i;
}

/** h4

	Esta heurística cuanta la cantidad de pancakes cuyo vecino
    difiere en más de 1, incluyendo el plato base.
	NOTA: A partir del valor anterior es posible calcular h4 dada la
    posición en la que se invertirán los pancakes, para evitar el ciclo
    y hacerlo en tiempo constante.
EJEMPLO:
	acbegdihf    6
REFERENCIA:
	Helmert, M. 2010. Landmark Heuristics for the Pancake Problem.
	In Proceedings of the Third Annual Symposium on Combinatorial
	Search.
*/
int h4(char *s)
{
	int i, c=0;


	if ( s[0]!='a'  &&  s[0]!='b' )
		c=1;
	for ( i=0; s[i+1] ; i++ )
		 if ( abs( s[i]-s[i+1] ) > 1 )
			c++;
	return c;
}

int h5(char *s)
{
	int i, c=0;

	for ( i=0; s[i+1] ; i++ )
		c += abs( s[i]-s[i+1] );
	return c/2-2;
}

/* Fin de archivo */
