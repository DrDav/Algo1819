#include <stdio.h>
#include <stdlib.h>
/* Definisco la costante N = 100.
    NB: per convensione le costanti vengono rappresentate con la lettera maiuscola */
#define N 100

int my_strlen(char *s){
    int len = 0;
    int i=0;
    while(s[i]){
        len++;
        i++;
    }   
    return len;
}

int main(void)
{
    char* s = malloc(N*sizeof(char));
    scanf("%s", s);
    
    printf("%d\n", my_strlen(s));

    return 0;
}
