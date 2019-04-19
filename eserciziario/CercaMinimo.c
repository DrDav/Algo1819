#include<stdio.h>
#define N 8

int min(int a, int b) {

    if(a < b) return a;
    else return b;
}

int CercaMinimo(int A[], int inizio, int fine) {

    int min1 = 0;
    int min2 = 0;

    if(fine - inizio > 2) {

        int m = (inizio + fine) / 2;
        min1 = CercaMinimo(A, inizio, m);
        min2 = CercaMinimo(A, m+1, fine);
    }
    else {
        min1 = inizio;
        min2 = fine;
    }
    
    // Prendi l'elemento
    int minimo = min(A[min1], A[min2]);

    // Restituisci l'indice del minimo
    if(minimo == A[min1]) return min1;
    else return min2;
}

int main(void) {


    int A[N] = {12, 14, 20, 1, 3, 7, 10, 11};

    int indice_minimo = CercaMinimo(A, 0, N-1);

    for(int i=0; i<N; i++) printf("%d ", A[i]);
    printf("\n");
    printf("Indice Minimo: %d\n", indice_minimo);

    return 0;
}