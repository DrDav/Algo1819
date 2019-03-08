#include <stdio.h>

int main(void) {
    int somma = 0;
    int input;

    do {
        scanf("%i", &input);
        somma += input;
    }
    while(input != 0);

    printf("%i", somma);

    return 0;
}
