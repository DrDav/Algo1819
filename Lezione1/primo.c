#include <stdio.h>

#define PRIMO(n) alg_meno_ovvio(n)

int alg_ovvio(int);
int alg_meno_ovvio(int);

int main(void) {
    int numero;

    scanf("%i", &numero);
    
    printf("%i", PRIMO(numero));

    return 0;
}

/* Complessità: Θ(n) - Pseudopolinomiale! */
int alg_ovvio(int n) {
    int i;

    if(n <= 1) {
        return 0;
    }

    for(i=2;i<n;i+=2) {
        if(n%i == 0) { // Se n è divisibile per i, allora... 
            return 0; // ... n non è primo (false)
        }
    }

    return 1; // Se arriviamo qua in fondo, allora n è primo (true)
}

/* Complessità Θ(√n) */
int alg_meno_ovvio(int n) {
    if (n <= 1) {
        return 0;
    }
    else if (n <= 3) {
        return 1; 
    }
  
    
    if (n%2 == 0 || n%3 == 0) {
        return 0; 
    }

    int i;
    /* Possiamo fermarci a √n perché un numero più grande di √n
     * è un multiplo di numeri che abbiamo già testato.
     * Possiamo partire da 5 perché 2 e 3 li abbiamo già controllati,
     * possiamo avanzare di 2 perché è inutile controllare i numeri pari
     * (sono già multipli di 2)
     */
    for(i=5;i*i<=n;i=i+2) {
        if(n%i == 0 || n%(i+2) == 0) {
           return 0; 
        }
    }
  
    return 1; 
}
