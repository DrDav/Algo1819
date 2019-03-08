#include <stdio.h>

#define N 10

void minmax(int array[], int dim, int *min, int *max) {
    int i;

    *min = 0;
    *max = 0;

    for(i=0;i<dim;i++) {
        if(array[i] < array[*min]) {
            *min = i;
        }
        else if(array[i] > *(array+(*max))) { // Equivalente a sopra
            *max = i;
        }
    }
}

int main(void) {
    int a[N];
    int pos_min, pos_max;
    int i;

    for(i=0;i<N;i++) {
        scanf("%i", &a[i]);
    }

    minmax(a, N, &pos_min, &pos_max);

    printf("%i\n%i\n%i\n%i", pos_min, a[pos_min], pos_max, a[pos_max]);

    return 0;
}
