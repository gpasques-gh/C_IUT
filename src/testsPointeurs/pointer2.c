#include <stdio.h>

int main()
{
    int a;
    int *pa;

    a = 4;
    pa = &a;

    *pa = 5;

    printf("a = %d", a);

    return 0;
}