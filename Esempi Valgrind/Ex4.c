#include <stdio.h>

#define N 5

int a[N];
int i;

int main(void) {
    i = 0;
    
    while(i<N) { /* Loop?! */
        a[++i] = 1;
        printf("Iterazione %i\n", i);
    }
    
    printf("Finito.\n");
    
    return 0;
}

