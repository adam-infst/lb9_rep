#include "gauss.h"
#include <stdio.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
	int i, j, k, p, s;
	int diagonal_length = mat->r < mat->c ? mat->r : mat->c;

	for (i = 0; i < diagonal_length; i++) {

		/* wybor elementu glownego */
		int do_zamiany = i;
		double maks_bezwzgledne = mat->data[i][i] >= 0 ? mat->data[i][i] : mat->data[i][i] * (-1);
		for (p = i+1; p < mat->r; p++) {

			double modul = mat->data[p][i] >= 0 ? mat->data[p][i] : mat->data[p][i] * (-1);
			if (modul > maks_bezwzgledne) {
				maks_bezwzgledne = modul;
				do_zamiany = p;
			}
		}
		if (do_zamiany != i) {

			for (s = 0; s < mat->c; s++) {
				double t = mat->data[i][s];
				mat->data[i][s] = mat->data[do_zamiany][s];
				mat->data[do_zamiany][s] = t;
			}
			double t = b->data[i][0];
			b->data[i][0] = b->data[do_zamiany][0];
			b->data[do_zamiany][0] = t;
		}

		double pivot = mat->data[i][i];
		if (pivot == 0) {
			fprintf(stderr, "[!] Blad dzielenia przez 0! Macierz jest osobliwa");
			return 1;
		}

		for (j = i+1; j < mat->r; j++) { /* zeruje po kolei elementy ponizej diagonalnej z tej kolumny */
		
			double el_value = mat->data[j][i]; /* element ktory chcemy wyzerowac */
			if (el_value == 0) continue;

			for (k = 0; k < mat->c; k++) {
				/* za pomoca petli mnozymy caly wiersz pzez pivot */
				mat->data[j][k] *= pivot;
				/* nowa wartosc zerowanego elementu bedzie teraz rowna el_value * pivot,
				wiec zeby go wyzerowac wystarczy el_value razy odjac wiersz z pivotem */
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