#include <stdio.h>
#include <stdlib.h>

#define N 13

/*
Sia A un array dininteri distinti.
Si consideri il problema di trovare la coppia (A[i],A[j]), con i != j, 
che minimizza la differenza in valore assoluto tra coppie di elementi, 
ovvero di trovare la coppia (A[i],A[j]) tale che: 
    | A[i]−A[j] | ≤ | A[k]−a[l] | . ∀ 1 ≤ k,l ≤ n, k != l.
*/

/*
Si usa il codice di heapsort di Heapsort.c
*/
int left(int i) { return (2*i)+1; }
int right(int i) { return (2*i)+2; }
int parent(int i) { return (i-1)/2; }

void swap(int* A, int i, int j) {
    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

typedef struct coppia {
    int i;
    int j;
} coppia;

// heapify 
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

// heapsort
void heapsort(int *A, int n) {

    for(int i=0; i<n; i++)
        heapify(A, n, i);
}

coppia cercaCoppia(int* array, int len) {

    heapsort(array, len);
    int diff = abs(array[1] - array[0]);
    coppia risultato;
    risultato.i = array[1];
    risultato.j = array[0];

    for(int i=2; i<len; i++) {
        
        int d = abs(array[i] - array[i-1]);
        if(d < diff) {

            diff = d;
            risultato.i = array[i];
            risultato.j = array[i-1];
        }
    }

    return risultato;
}

int main(void) {

    int array[13] = {17, 14, 16, 10, 5, 8, 1, -1, 2, -10, 20, 4, -3};

    printf("Array di input:\n");
    for(int i=0; i<N; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");

    coppia c = cercaCoppia(array, N);

    printf("Elementi risultanti:\n");
    printf("<%d, %d>\n", c.i, c.j);

    return 0;
}