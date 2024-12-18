#include "gauss.h"
#include <stdio.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
	int i, j, k;
	int diagonal_length = mat->r < mat->c ? mat->r : mat->c;

	for (i = 0; i < diagonal_length; i++) {
		double pivot = mat->data[i][i];

		if (pivot == 0) return 1;

		for (j = i+1; j < mat->r; j++) /* zeruje po kolei elementy ponizej diagonalnej z tej kolumny */
		{
			double el_value = mat->data[j][i]; /* element ktory chcemy wyzerowac */
			if (el_value == 0) continue;

			for (k = 0; k < mat->c; k++)
			{
				/* za pomoca petli mnozymy caly wiersz pzez pivot */
				mat->data[j][k] *= pivot;
				/* nowa wartosc elementu bedzie teraz rowna el_value * pivot, wiec zeby go wyzerowac 
				wystarczy el_value razy odjac wiersz z pivotem */
				mat->data[j][k] -= mat->data[i][k] * el_value;
			}
			/* trzeba wykonac ta sama operacje na macierzy zmiennych */
			b->data[j][0] *= pivot;
			b->data[j][0] -= b->data[i][0] * el_value;
		}
	}

	return 0;
	/* wazne: macierz 3x3 zaczyna sie mat->dane[0][0] i konczy mat->dane[2][2] */
}