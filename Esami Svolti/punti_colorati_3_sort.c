/*
 * Esame - Punti Colorati
 * Il testo di questo esame si trova nella Lezione 7 sul portale esercizi.
 * Versione con 3 sort (inefficiente)
 *
 * Link: http://algo1819.dijkstra.di.unipi.it/#/task/Lez0701LEDRMH_dup_dup_dup___dup/statement
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    int c;
} point_t;

/* Confronto tra le componenti x di un point_t (per qsort) */
int pnt_cmp_x(const void* a, const void* b) {
    const point_t *p1 = *(const point_t**) a;
    const point_t *p2 = *(const point_t**) b;

    return (p1->x - p2->x);
}

/* Confronto tra le componenti x di un point_t (per qsort) */
int pnt_cmp_y(const void* a, const void* b) {
    const point_t *p1 = *(const point_t**) a;
    const point_t *p2 = *(const point_t**) b;
    
    return (p1->y - p2->y);
}

/* Confronto tra le componenti x di un point_t (per qsort) */
int pnt_cmp_c(const void* a, const void* b) {
    const point_t *p1 = *(const point_t**) a;
    const point_t *p2 = *(const point_t**) b;
    
    return (p1->c - p2->c);
}

int query(point_t** punti, int n, int x1, int y1, int x2, int y2) {
    int i;
    
    qsort(punti, n, sizeof(point_t*), pnt_cmp_x);
    
    /* Punti è ordinato su x */
    int start = 0;
    int end = n-1;
    
    /* Cerca il primo punto con x >= x1 (scansione) */
    while(start < n && punti[start]->x < x1)
        start++;
    
    /* Cerca l'ultimo punto con x <= x2 (scansione al contrario) */
    while(end >= start && punti[end]->x > x2)
        end--;
    
    if(start <= end) { // C'è almeno un punto che soddisfa questi vincoli
        /* Ordina il sottoarray trovato sulla componente y
         * (contiene end-start+1 elementi)
         */
        qsort(punti + start, end - start + 1, sizeof(point_t*), pnt_cmp_y);
        
        while(start < n && punti[start]->y < y1)
            start++;
        
        while(end >= start && punti[end]->y > y2)
            end--;
        
        if(start <= end) { // Il rettangolo non è vuoto
            /* Ordina il sottoarray trovato per colore */
            qsort(punti + start, end - start + 1, sizeof(point_t*), pnt_cmp_c);
            
            /* Ricerca dei colori distinti */
            int colori = 1;
            for(i=start;i<end;i++) {
                if(punti[i]->c != punti[i+1]->c)
                    colori++;
            }
            
            return colori;
        }
    }
    
    return 0; // Non ci sono punti nel rettangolo => 0 colori
}

int main(void) {
    int i;
    int n, m;

    scanf("%i %i", &n, &m);

    /* Allocazione dell'array di (puntatori a) punti */
    point_t** punti = malloc(n * sizeof(point_t*));

    for(i=0;i<n;i++) {
        /* Allocazione di un nuovo punto */
        point_t *pnt = malloc(sizeof(point_t));

        scanf("%i %i %i", &(pnt->x), &(pnt->y), &(pnt->c));

        punti[i] = pnt;
    }

    /* Interrogazioni */
    for(i=0;i<m;i++) {
        int x1, y1, x2, y2;

        scanf("%i %i %i %i", &x1, &y1, &x2, &y2);

        printf("%i\n", query(punti, n, x1, y1, x2, y2));
    }

    /* Deallocazione della memoria */
    for(i=0;i<n;i++)
        free(punti[i]); // Ogni punto contenuto nell'array

    free(punti); // L'array di punti


    return 0;
}
