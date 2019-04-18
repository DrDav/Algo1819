#include <stdio.h>
#include <stdlib.h>

/**
 * Implementazione di un heap di massimo
 * Heap di minimo è analogo
 * 
 * Un heap di massimo è un albero, rappresentabile anche tramite array, in cui ogni nodo
 * è maggiore di tutti i nodi dei due sotto-alberi. In questo modo abbiamo l'elemento di massimo
 * sempre presente sulla radice dell'albero, o prima posizione dell'array.
 * 
 * 
 * La funzione heapify() è la funzione importante che, dato un indice i di un elemento "fuori posto"
 * nello heap, lo riorganizza a partire da quell'indice
 *  
 */

// Funzioni di appoggio da utilizzare nella funzione heapify

    // Ottieni indice figlio sinistro di un array heap
int left(int i) {
    
    return (2*i)+1;
}

    // Ottieni indice figlio destro di un array heap
int right(int i) {

    return (2*i)+2;
}

    // Ottieni indice padre di un array heap
int parent(int i) {

    return (i-1)/2;
}

    // Dato un array, scambia 2 elementi alle posizioni (i, j)
void swap(int* A, int i, int j) {

    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}



// heapify 
    // Data una struttura heap rirpistinare la proprietà heap violata dall'i-esimo elemento
    // heap: array di interi che costituiscono l'heap
    // n: dimensione dell'heap
    // i: elemento che viola la proprietà heap

    // Se uno dei 2 figli è maggiore dell'elemento i, allora scambia il figlio con il padre
    // e chiama heapify partendo dal nodo figlio perché questo scambio potrebbe aver violato
    // la proprietà heap su quel sotto albero

    // Complessità: log(n), altezza albero
void heapify(int* heap, int n, int i) {

    int left_i = left(i);
    int right_i = right(i);
    int largest = 0;

    if(left_i < n && heap[left_i] > heap[i])
        largest = left_i;
    else if(right_i < n && heap[right_i] > heap[i])
        largest = right_i;
    else
        largest = i;

    if(largest != i) {
        swap(heap, i, largest);
        heapify(heap, n, i);
    }
}


// build_max_heap
    // Dato un array, trasformarlo in un heap array chiamando heapify() su ogni elemento
    // Nota, A stesso diventa un heap array
    // A: array di partenza
    // n: dimensione di A

    // Complessità: n*log(n)
void build_max_heap(int *A, int n) {

    for(int i=n-1; i>=0; i--)
        heapify(A, n, i);
}

// extract
    // estrae il primo elemento dell'array heap; ripristina la proprietà
    // heap: array heap
    // *n: puntatore ad n, perché ci serve modificarlo per ricordarci la riduzione
    // return int* heap: siccome con allochiamo nuovamente heap per fare spazio all'elemento extram si restuisce questa
        // nuova porzione di memoria dia heap

    // Sovrascrivi elemento 0 con l'ultimo elemento
    // decrementa n
    // rialloca heap array
    // heapify dall'elemento 0 perché viola la proprietà heap
int* extract(int* heap, int* n) {

    heap[0] = heap[(*n) - 1];
    (*n)--;

    heap = realloc(heap, (*n) * sizeof(int));

    heapify(heap, *n, 0);

    return heap;
}

// insert
    // Inserisci un elemento nello heap e ripristina la proprietà heap; salva in n la nuova dimensione
    // heap: l'array heap
    // *n: puntatore ad n, perché ci serve modificarlo per ricordarci l'incremento
    // el: l'elemento da aggiungere
    // return int* heap: siccome con allochiamo nuovamente heap per fare spazio all'elemento extram si restuisce questa
        // nuova porzione di memoria dia heap

    // salva una copia del valore di n
    // incrementa n (siccome n è passato come puntatore la modifica si riflette a chiamata terminata)
    // usa realloc per estendere l'array heap da dimensione n a dimensione (n+1)
    // inserisci in fondo all'array l'elemento el
    // propaga in alto, di padre in padre, el fino a che la proprietà heap è soddisfatta

    // complessità: log(n)
int* insert(int* heap, int* n, int el) {

    int i = *n;
    (*n)++;
    heap = realloc(heap, (i+1) * sizeof(int));

    while(i > 0 && el > heap[parent(i)]) {
        
        int p = parent(i);
        heap[i] = heap[p];
        i = p;
    }

    heap[i] = el;

    return heap;
}

// Leggi, senza estrarre, il primo elemento di un heap
int get(int* heap) {

    return heap[0];
}



int main() {

    // Array iniziale
    int n = 6;
    int A[6] = {6, 14, 10, 9, 2, 1};

    // Creazione di heap come array dinamico
        // Inserisci elementi di A
    int* heap = (int*) malloc(n*sizeof(int));
    for(int j=0; j<n; j++)
        heap[j] = A[j];


    printf("Array di partenza:\n");
    for(int j=0; j<n; j++)
        printf("%d ", heap[j]);
    printf("\n");


    // Riorganizza array heap secondo la struttura heap di massimo
    build_max_heap(heap, n);


    printf("Heap derivato:\n");
    for(int j=0; j<n; j++)
        printf("%d ", heap[j]);
    printf("\n");

    // Aggiungi 3 elementi
    printf("Aggiungo elementi 20, 15, 5:\n");

    heap = insert(heap, &n, 20);
    heap = insert(heap, &n, 15);
    heap = insert(heap, &n, 5);

    printf("Stato dell'heap:\n");
    for(int j=0; j<n; j++)
        printf("%d ", heap[j]);
    printf("\n");


    // Ottieni elemento di massimo
    printf("Elemento maggiore: %d\n", get(heap));


    // Estrai i primi 2 elementi di massimo
    printf("Estraggo i primi 2 elementi:\n");

    heap = extract(heap, &n);
    printf("\tElemento maggiore: %d\n", get(heap));
    heap = extract(heap, &n);
    printf("\tElemento maggiore: %d\n", get(heap));


    printf("Stato dell'heap:\n");
    for(int j=0; j<n; j++)
        printf("%d ", heap[j]);
    printf("\n");

    // Dealloca l'array
    free(heap);

    return 0;
}