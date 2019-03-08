#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    int a, b;

    scanf("%i", &a);
    scanf("%i", &b);

    swap(&a, &b);

    printf("%i\n%i", a, b);

    return 0;
}
