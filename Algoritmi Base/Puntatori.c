#include<stdio.h>

/**
 * 
 * Piccolo esempio sui puntatori, sperando di risolvere qualche confusione, che all'inizio ci sta
 * 
 * Ripasso:
 * 
 * int b = 30;
 * 
 *  b e' una variabile
 *  b = valore di b = 30
 *  &b = indirizzo di memoria di b = 0x123 (assunto)
 * 
 * 
 * 
 * int* a = &b;
 * 
 *  a e' un indirizzo, che nel nostro caso e' un puntatore ad intero
 *  a = valore di a = indirizzo di b = 0x123
 *  &a = indirizzo di memoria di a = 0x234 (assunto)
 *  *a = valore del puntatore di a
 *     = siccome a punta a b
 *     = valore di b
 *     = 30
 * 
 * 
 * Proviamo con un esempio grafico
 * 
 * questa è la memoria: cella ha l'indirizzo in formato 0x123 oppure 0x534 etc
 * 
 * |  var-valore  | "indirizzo"
 *  --------------
 * |  var-valore  | "indirizzo"
 *  --------------
 *       ...
 * 
 * 
 * int b = 30 :: salva b in una cella di memoria ad indirizzo 0x123
 * 
 * |  b-30  | "0x123"
 *  --------
 * |   ...  | "..."
 *  --------
 *     ...
 *
 * printf("%d", b) ==> stampa valore di b
 *                 ==> contenuto della cella di memoria di b
 *                 ==> stampa 30
 * 
 * printf("%p", &b) ==> stampa indirizzo di b
 *                  ==> stampa 0x123
 * 
 * 
 * int* a = &b
 * 
 * |    b-30    | "0x123"
 *  --------
 * |     ...    | "..."
 *  ------------
 * |   a-0x123  | "0x234"
 *  ------------
 *       ...
 *  
 * 
 * printf("%d", a) ==> stampa il valore di a
 *                 ==> contenuto della cella di memoria di a
 *                 ==> a e' un indirizzo (puntatore) a (cella) di b 
 *                 ==> stampa 0x123
 * 
 * printf("%p", &a) ==> stampa indirizzo di a
 *                  ==> a avra' un proprio indirizzo di memoria
 *                  ==> stampa 0x234
 * 
 * printf("%d", *a) ==> stampa valore della cella di memoria puntata da a
 *                  ==> questa cella di memoria è 0x123, che è la cella di b
 *                  ==> quindi stampa il valore della cella di memoria di b
 *                  ==> stampa 30
*/

int main() {

    int b = 30;
    int *a;
    a = &b;

    ////
    // printf, opzione %d: stampa un numero decimale (valori tra 0-9)
    // printf, opzione %p: stampa un "puntatore", ovvero una locazione di memoria in esadecimale (valori da 0-9, a-f)
    ////

    printf("\n");
    printf("int b = 30;\nint *a;\n a = &b;\n");
    printf("Valore di b, b:  %d\n", b);
    printf("Indirizzo di b, &b:  %p\n", &b);
    printf("----\n");
    printf("Valore di a, a:  %p     (dovrebbe essere uguale a &b)\n", a);
    printf("Indirizzo di a, &a:  %p     (leggermente diverso da &b)\n", &a);
    printf("Valore dell'indirizzo puntato da a, *a =  %d     (dovrebbe essere il valore di b)\n", *a);

    // printf("%d\n", &b) stampa la conversione in decimale del puntatore, DA WARNING


    ////
    // Esempio scorretto
    ////

    a = b; // senza &, DA WARNING

    // In questo momento la cella di a contiene l'indirizzo di memoria 30 (0x1e in esadecimale)
    printf("----\n");
    printf("a = b; (manca &)\n");
    printf("Valore di a, a:  %p     (30 in esadecimale, ovvero il valore di b)\n", a);
    printf("Indirizzo di a, &a:  %p     \n", &a);
    
    // // Il comando sotto da segmentation fault perché *a è il valore di memoria alla locazione 0x1e
    // // che probabilmente il nostro programma non ha accesso
    
    // printf("Valore dell'indirizzo puntato da a, *a =  %d     (dovrebbe essere il valore di b)\n", *a);

    printf("\n");
    return 0;
}