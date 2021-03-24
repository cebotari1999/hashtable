// Copyright 2020 CebotariZinaida

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 2000001

int main() {
    /*
    * Vectorul de fregventa (v_freq), este un unsigned char, 
    * pentru ca stim ca valoarea maxima pe care putem s-a o stocam
    * intr-un element din vector este 256 
    */

    unsigned char *v_freq = malloc(MAX * sizeof(unsigned char));
    int q;

    /* Initializam vecotrul */
    for (int i = 0; i < MAX; i++) {
        v_freq[i] = 0;
    }

    /* Cat timp are ce citi de la stdin, citeste si incrementeaza 
    * cu 1, elementele de pe pozitiile citite */
    while (fscanf(stdin, "%d", &q) != EOF) {
        v_freq[q] = v_freq[q] + 1;
    }

    /* Se afiseaza elementele nenule din vector si pozitia lor */
    for (int i = 0; i < MAX; i++) {
        if (v_freq[i] != 0) {
            printf("%d %d\n", i, v_freq[i]);
        }
    }
    free(v_freq);
    return 0;
}
