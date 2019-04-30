#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 

/* Questa funzione partiziona l'array A in 3 parti:
    1) A[sx..i] contiene tutti gli elementi minori del pivot; 
    2) A[i+1..j-1] contiene tutti gli elementi uguali al pivot; 
    3) A[j..dx] contiene tutti gli elementi maggiori del pivot. */ 
void distribuzione(int A[], int sx, int dx, int* i, int* j) { 
  
    // Variabile per scorrere l'array
    int s = sx; 

    // Prendo come pivot l'ultimo elemento dell'array
    int pivot = A[dx]; 

    while (s <= dx) 
    { 
        if (A[s]<pivot) 
            swap(&A[sx++], &A[s++]); 
        else if (A[s]==pivot) 
            s++; 
        else if (A[s]>pivot) 
            swap(&A[s], &A[dx--]); 
    } 
  
    // Aggiorno i e j
    *i = sx-1; 
    *j = s;
}

// Quick Sort basato su 3-way partition
void quicksort(int A[], int sx, int dx) { 
 
    // Caso base con 1 o 0 elementi
    if(sx>=dx)
        return;

    int i, j;
  
    // NB: i e j passati per riferimento! 
    distribuzione(A, sx, dx, &i, &j); 

    //printf("perno1: %d", i);
    //printf("perno2: %d", j);
  
    // Ricorsione su elementi minori del pivot 
    quicksort(A, sx, i); 
    // Ricorsione su elementi maggiori del pivot
    quicksort(A, j, dx); 
}  

void stampaArray(int A[], int n) { 
    for (int i = 0; i < n; ++i) 
        printf("%d ", A[i]);
    printf("\n"); 
} 

int main(void){
    int N;

    scanf("%i", &N); 

    int *A = malloc(N*sizeof(int));

    for(int i = 0; i < N; i++)
    {
        scanf("%i", &A[i]);
    }

    quicksort(A, 0, N-1);
    
    stampaArray(A, N);

    return 0;
} 