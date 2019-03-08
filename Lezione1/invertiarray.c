#include <stdio.h>

#define MAX_N 10000

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main(void) {
    int array[MAX_N];
    int dim;
    int i;

    scanf("%i", &dim);
    for(i=0;i<dim;i++) {
        scanf("%i", &array[i]); // In alternativa si può scrivere: array + i
    }

    for(i=0;i<dim/2;i++) {
        swap(&array[i], &array[dim-i-1]);
    }

    for(i=0;i<dim;i++) {
        printf("%i\n", array[i]);
    }

    return 0;
}
