#include <stdio.h>

// Fonction qui échange 2 valeurs à l'aide d'une variable temporaire
void swapTemp(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

// Fonction qui échange 2 valeurs avec des XOR
void swapXor(int *a, int *b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

// Fonction qui échange 2 valeurs avec des additions et soustractions
void swapAdd(int *a, int *b) 
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void swapAddresses(int **a, int **b) 
{
    int** c = a;
    a = b;
    b = c;
}

void main()
{
    // Variables
    int a, b;
    a = 4;
    b = 1;
    int* ptrA = &a;
    int* ptrB = &b;

    // Echange des valeurs
    swapAddresses(&ptrA, &ptrB);
    
    


    // Affichage du résultat
    printf("a = %d\nb = %d\n", *ptrA, *ptrB);
}