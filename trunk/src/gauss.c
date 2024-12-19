#include "gauss.h"
#include <stdio.h>
#include <math.h> //potrzebna do fabs

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
	int i, j, k;
	int diagonal_length = mat->r < mat->c ? mat->r : mat->c;


	for (i = 0; i < diagonal_length; i++) {

        /// ROZSZERZENIE O WYBÓR ELEMENTU GŁÓWNEGO - student A - branch diag_elem1

        // znajduje wiersz z największą wartością (bezwzględną - fabs) elementu w danej kolumnie

        int max_row = i;
        double max_wart = fabs(mat->data[i][i]);

        for (j = i + 1; j < mat->r; j++) {
            if (fabs(mat->data[j][i]) > max_wart){
                max_row = j;
                max_wart = fabs(mat->data[j][i]);
            }
        }

     // jak max_wart == 0, macierz jest osobliwa (nie dalo by sie podzielic przez zero)
        if (max_wart == 0)
            return 1;

        // zamiana wierszy, jeśli wiersz z max wartością, nie jest bieżącym wierszem
        if (max_row != i) {
            for (k =0; k < mat->c; k++){

                double temp = mat->data[i][k];  //zamiana
                mat->data[i][k] = mat->data[max_row][k];
                mat->data[max_row][k] = temp;
            }
            // zamiana wierszy, tyle że teraz dla macierzy b (macierz zmiennych)
            double temp_b = b->data[i][0];
            b->data[i][0] = b->data[max_row][0];
            b->data[max_row][0] = temp_b;
        }

        /// ROZSZERZENIE O WYBÓR ELEMENTU GŁÓWNEGO - koniec zmian.

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
