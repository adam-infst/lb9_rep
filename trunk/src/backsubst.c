#include "backsubst.h"
#include <stdio.h>
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */

int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
    // Czy dobry rozmiar? warunki na "n" na "n" itd.
    if (mat->r != mat->c || mat->r != b->r || b->c != 1 || x->r != b->r || x->c != 1) {
        fprintf(stderr, "[!] Blad! Nieprawidlowe wymiary macierzy.\n");
        return 2;
    }

    int n = mat->r;  // macierz jest n x n, tyle samo rzędów co kolumn, więc biore np. rząd
    int i, j;


    for (i= n - 1; i >= 0; i--) {   // dlatego n - 1, bo np. w maciezy 3x3, ostatni element ma współrzędne data[2][2], bo indeksy zaczynają się od zera
        if (mat->data[i][i] == 0){
            fprintf(stderr, "[!] Blad dzielenia przez 0! Element na diagonali = 0.\n");
            return 1;
        }

        // obliczenie "x"
        double sum = 0.0;
        for (j = i+1; j < n; j++){
            sum += mat->data[i][j] * x->data[j][0];
        }
        x->data[i][0] = (b->data[i][0] - sum) / mat->data[i][i];
    }

    return 0;
}
