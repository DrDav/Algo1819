#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100 /* Lunghezza massima di una stringa */

/*
 * Coppia (stringa, intero)
 * Tiene traccia di quante volte una stringa appare nella sequenza
 */
typedef struct {
    char* str;
    int count;
} str_counter_t;


/*
 * Confronta due struct di tipo str_counter_t
 * in base alla seconda componente (int)
 */
int counter_cmp_count(const void* a, const void* b) {
    const str_counter_t* s1 = *(const str_counter_t**) a;
    const str_counter_t* s2 = *(const str_counter_t**) b;

    return -(s1->count - s2->count); // Decrescente
}

/*
 * Confronta due struct di tipo str_counter_t
 * in base alla prima componente (stringa)
 */
int counter_cmp_str(const void* a, const void* b) {
    const str_counter_t* s1 = *(const str_counter_t**) a;
    const str_counter_t* s2 = *(const str_counter_t**) b;

    return strncmp(s1->str, s2->str, MAX_LENGTH);
}

/* Confronto tra due stringhe per qsort */
int my_strcmp(const void* a, const void* b) {
    return strncmp(*(const char**)a, *(const char**)b, MAX_LENGTH);
}

/*
 * Conta le occorrenze di ogni stringa e
 * restituisce un array di strutture str_counter_t,
 * ovvero un array di coppie (stringa, frequenza)
 */
str_counter_t** count_occurrences(char** s, int n, int* c_length) {
    int i, j;
    /* Ordinamento delle stringhe */
    qsort(s, n, sizeof(char*), my_strcmp); // O(n log n)

    i = 1; // Partiamo da 1 per confrontarci con la stringa precedente
    j = 0; // Utilizzato per popolare C

    /* Creazione dell'array di coppie (stringa, frequenza) */
    str_counter_t** C = malloc(n * sizeof(str_counter_t *));

    while(i < n) {
        /* Contiamo le occorrenze di ogni stringa
         * con una scansione dell'array ordinato
         */
        int count = 1; // Almeno un'occorrenza di ogni stringa c'è
        while(i < n && strncmp(s[i], s[i-1], MAX_LENGTH) == 0) {
            count++;
            i++;
        }

        /* Usciti dal while possiamo inserire
         * una nuova coppia nell'array C */
        str_counter_t* coppia = malloc(sizeof(str_counter_t));
        coppia->str = s[i-1];
        coppia->count = count;

        C[j] = coppia;
        j++; // Avanza in C

        i++; // Avanza nell'array con la prossima stringa
    }

    *c_length = j; // Per restituire anche la lunghezza di C

    return C;
}

/* Complessità: O(n log n) */
int main(void) {
    int i;
    int n, k;
    char** stringhe;
    int dim_c;

    scanf("%i",&n);
    scanf("%i",&k);

    /* Allocazione dell'array di stringhe */
    stringhe = malloc(n * sizeof(char*));

    for(i=0;i<n;i++) {
        /* Ogni stringa dell'array deve essere prima allocata */
        stringhe[i] = malloc((MAX_LENGTH + 1) * sizeof(char)); // +1 per \0

        scanf("%s", stringhe[i]);
    }

    str_counter_t** C = count_occurrences(stringhe, n, &dim_c);

    /* Ordina tutto C in base alla seconda componente,
     * cioè per frequenza decrescente
     */
    qsort(C, dim_c, sizeof(str_counter_t*), counter_cmp_count); // O(n log n)
    /* Ordina C in base alla prima componente,
     * cioè alla stringa.
     * NB: Solo le prime K posizioni, che sono quelle che ci interessano.
     */
    qsort(C, k, sizeof(str_counter_t*), counter_cmp_str); // O(k log k)

    /* Stampa del risultato */
    for(i=0;i<k;i++)
        printf("%s\n", C[i]->str);

    /* Deallocazione della memoria (!) */
    for(i=0;i<dim_c;i++)
        free(C[i]); // Le struct contenute in C

    free(C); // L'array C

    for(i=0;i<n;i++)
        free(stringhe[i]); // Le singole stringhe di input

    free(stringhe); // L'array di input

    return 0;
}
