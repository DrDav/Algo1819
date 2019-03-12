#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1001 // + 1 per il carattere terminatore della stringa: '\0'

/* Cambiare questa define per scegliere quale funzione chiamare */
#define PROD(str, k) product_senza_librerie(str, k)


/* Versione usando funzioni di libreria (strcpy, strcat) */
char* product(char *str, int k) {
    int length = strlen(str);
    char *product = malloc((length + 1) * sizeof(char)); // +1 per il '\0'
    int i;

    /* Inizializzazione di product con la prima copia della stringa */
    strncpy(product, str, length);
    /* Aggiunta delle altre k-1 copie */
    for(i=1;i<k;i++) {
       strncat(product, str, length);
    }

    return product;
}

char* product_senza_librerie(char *str, int k) {
    int i, j;
    int length = 0;

    // Ciclo che calcola la lunghezza di str.
    while(str[length] != '\0') {
        length++;
    }
    char *product = malloc((length+1) * sizeof(char));

    /* Copia della stringa per k volte */
    for(i=0;i<k;i++) {
        for(j=0;j<length;j++) {
            /* Dobbiamo tenere conto di length per non sovrascrivere la stringa */
            product[j + length*i] = str[j];
        }
    }

    product[j + length * i] = '\0'; // Aggiungiamo il carattere terminatore

    return product;
}

int main(void) {
    int k;
    char stringa[MAX];

    scanf("%s", stringa);
    scanf("%i", &k);

    printf("%s", PROD(stringa, k));

    return 0;
}
