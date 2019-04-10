#include<stdio.h>

/**
 * 
 * Capire come funziona il qsort() implementando una map()
 * 
 * 
 * Se ricordate, una map() è una funzione di ordine superiore che
 * data una funzione "func" e una lista "A" (array nel nostro caso)
 * applica "func" a tutti gli elementi di "A"
 * 
 * pseudo:
 * 
 *  for(i=0; i<len, i++)
 *    A[i] = func(A[i])
 * 
 * qsort() funziona allo stesso modo con compare() come nostra func()
 * Come si fa a passare una funzione come parametro?
 *  La sintassi e' un po' strana, ma ci si puo' fare l'abitudine
 * 
*/


// Definizione di qsort
    // base: puntatore a void, che determina un array di void, void[]
        // void perche' qsort non sa a priori che tipo di array deve andare a ordinare (interi, stringhe etc)
    // nitems: lunghezza dell'array. size_t è un tipo per identificare una dimensione
    // size: dimensione degli elementi dell'array, dimensione restituita da sizeof("tipo")
        // non sapendo il tipo dell'array che qsort andra' ad ordinare, non sa nemmeno quanto e'
        // grande ogni elemento. Immagino che questo parametro serva a qsort per saltare di size in size in memoria
    // compare: la funzione di paragone che, dati 2 puntatori a void (sempre, perche' a priori il tipo dell'array
        // non e' noto) restituisci un intero che sta a significare se sono uguali, il primo e' maggiore del secondo
        // o viceversa. Applicando questa funzione quando c'e' da fare il paragone determina come l'array verra' ordinato
void qsort(void *base, 
            size_t nitems, 
            size_t size, 
            int (*compare)(const void *, const void*));


// Scriviamo la funzione map()
    // Anziche' usare void* useremo int* per semplicita'
    // map() avra' bisogno dell'array di interi e la sua lunghezza (sempre espressa in int)

    // A: array di int (oppure puntatore a int) (base di qsort)
    // len: lunghezza array (nitems di qsort)
    // func: funzione che, dato un puntatore a intero restituisce un intero, ovvero applica una modifica a questo intero

void map(int (*func)(const int* el), int* A, int len) {

    // Applica la funzione func ad ogni elemento dell'array di input
    for(int i=0; i<len; i++) {
        A[i] = func(&A[i]);
    }

    return;
}

// Scriviamo 2 funzioni per func()

    // const e' una parola chiave che "vincola" la variabile ad essere costante, ovvero che non puo' cambiare valore
int incrementa(const int* a) {

    return (*a)+1;
}

int raddoppia(const int* a) {

    return (*a)*2;
}


int main() {

    int array[5] = {4, 1, 3, 4, 1};
    
    for(int i=0; i<5; i++) printf("%d ", array[i]);
    printf("\n");

    map(incrementa, array, 5);

    // Ogni elemento dell'array dovrebbe essere aumentato di 1
    for(int i=0; i<5; i++) printf("%d ", array[i]);
    printf("\n");

    map(raddoppia, array, 5);

    // Ogni elemento dell'array, dopo l'incremento, dovrebbe essere raddoppiato
    for(int i=0; i<5; i++) printf("%d ", array[i]);
    printf("\n");

    // Mai provato a stampare una funzione con printf?
    // printf("%p\n", incrementa);
    // printf("%p\n", raddoppia);
    // printf("%p\n", map);


    return 0;

    /**
     * Questa cosa di passare le funzioni come parametro e' utile perche' altrimenti un programmatore dovrebbe
     * implementare la map() che incrementa, la map() che raddoppia etc come funzioni separate
     * 
     * uguale per qsort. Non importa implementare qsort su stringhe, qsort su interi, qsort su struct banane etc
     * 
    */

}