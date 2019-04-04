#include <stdio.h>
#define N -100000

struct Coppia { int el1; int el2; };

int max(int a, int b) {
    if(a > b) return a;
    else return b;
}

struct Coppia secondo(int A[], int i, int j) {

    if(j < i) {
        struct Coppia c;
        c.el1 = N;
        c.el2 = N;
        return c;
    }
    if(j == i) {
        struct Coppia c;
        c.el1 = A[i];
        c.el2 = N;
        return c;
    }

    int m = (i+j)/2;
    struct Coppia c1 = secondo(A, i, m);
    struct Coppia c2 = secondo(A, m+1, j);

    int p;
    int s;

    p = max(c1.el1, c2.el1);
    if(p == c1.el1) s = max(c1.el2, c2.el1);
    else s = max(c2.el2, c1.el1);

    struct Coppia c;
    c.el1 = p;
    c.el2 = s;

    printf("i)%d j)%d <%d, %d>\n", i, j, c.el1, c.el2);

    return c;
}

int main() {

    int a[7] = {11,6,1,3,5,2,8};
    int b[13] = {11,13,4,6,1,19,3,5,22,2,8,90,54};

    struct Coppia c;

    c = secondo(a, 0, 6);
    printf("%d %d\n", c.el1, c.el2);
    printf("Soluzione: %d\n\n", c.el2);
    c = secondo(b, 0, 12);
    printf("%d %d\n", c.el1, c.el2);
    printf("Soluzione: %d\n\n", c.el2);


    return 0;
}