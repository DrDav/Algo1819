#include <stdlib.h> // malloc() 

int main(void) {
    int *a = malloc(10 * sizeof(int));

    a[10] = 0;

    return 0;
}
