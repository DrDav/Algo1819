#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int val, i;

    int* frequenze = malloc(10*sizeof(int));

    scanf("%d", &val);

    while(val!=-1){
        if(val<-1 || val>9){
            printf("I numeri devono essere compresi tra 0 e 9.");
            return 0;
        }
        else
        {
            frequenze[val]++;
        }
        scanf("%d", &val);
    }
    
    for(i = 0; i < 10; i++)
    {
        printf("%d\n", frequenze[i]);
    }
    
    return 0;
}
