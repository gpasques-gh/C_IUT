#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Fonction affichant une matrice */
void printMat(int **mat, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

/* Fonction principale */
int main(int argc, char const *argv[])
{
    int r1 = atol(argv[1]);
    int c1 = atol(argv[2]);
    int r2 = atol(argv[3]);
    int c2 = atol(argv[4]);

    int count = 0;
    int numMat = 1;
    char buffer[256];
    char *sep = " ";

    int **mat1 = malloc(sizeof(int *) * r1);
    for (int i = 0; i < r1; i++)
    {
        mat1[i] = malloc(sizeof(int) * c1);
    }

    int **mat2 = malloc(sizeof(int *) * r2);
    for (int i = 0; i < r2; i++)
    {
        mat2[i] = malloc(sizeof(int) * c2);
    }

    int lines = 0;
    int rows;
    while (scanf("%99[^\n]", buffer) != EOF)
    {
        getchar();
        if (buffer[0] == '\r' && numMat == 1)
        {
            numMat = 2;
            lines = 0;
        } 
        else
        {
            rows = 0;
            char *token = strtok(buffer, sep);

            while (token != NULL)
            {
                if (numMat == 1)
                {
                    mat1[lines][rows] = atol(token);
                }
                else
                {
                    mat2[lines][rows] = atol(token);
                }
                token = strtok(NULL, sep);
                rows++;
            }
            lines++;
        }
        
    }

    int **matMult = malloc(sizeof(int *) * r1);
    for (int i = 0; i < r1; i++)
    {
        matMult[i] = malloc(sizeof(int) * c2);
    }

    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            for (int k = 0; k < c1; k++)
            {
                matMult[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    printf("Premiere matrice :\n");
    printMat(mat1, r1, c1);
    printf("Deuxieme matrice :\n");
    printMat(mat2, r2, c2);
    printf("Resultat de la multiplication des 2 matrices :\n");
    printMat(matMult, r1, c2);
    
    return 0;
}
