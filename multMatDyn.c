#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void chargerMatrices(int **mat1, int **mat2, FILE *fichier)
{    
    int bufferLength = 255;
    char buffer[255];
    char *seps = " ";
    int i1 = 0, j1 = 0, i2 = 0, j2 = 0;
    int numMat = 1;
    int number;

    while (fgets(buffer, bufferLength, fichier))
    {
        j1 = 0;
        j2 = 0;
        if (buffer[0] != '\n')
        {
            buffer[strcspn(buffer, "\n")] = 0;
            char *token = strtok(buffer, seps);
            while (token != NULL)
            {
                if (token != NULL)
                {
                    number = atol(token);

                    token = strtok(NULL, seps);
                    if (numMat == 1)
                    {
                        mat1[i1][j1] = number;
                        j1++;
                    }
                        
                    else if (numMat == 2)
                    {
                        mat2[i2][j2] = number;
                        j2++;   
                    }
                }
            }

            if (numMat == 1)
            {
                i1++;
            }
            else if (numMat == 2)
            {
                i2++;
            }
        }
    }
}

void afficherMatrice(int r, int c, int **mat)
{    
    for (int i = 0; i < r; i++)
    {
        if (i != 0)
            printf("\n");
        for (int j = 0; j < c; j++)
            printf("%d ", mat[i][j]);
    }
}

bool verifFichier(int r1, int c1, int r2, int c2, FILE *fichier)
{

    int bufferLength = 255;
    char buffer[255];
    char *seps = " ";
    int i1 = 0, j1 = 0, i2 = 0, j2 = 0, sj1 = 0, sj2 = 0;
    int numMat = 1;

    while (fgets(buffer, bufferLength, fichier))
    {
        j1 = 0;
        j2 = 0;
        if (buffer[0] != '\n')
        {
            buffer[strcspn(buffer, "\n")] = 0;
            char *token = strtok(buffer, seps);
            while (token != NULL)
            {
                for (int i = 0; i < strlen(token); i++)
                {
                    if (!isdigit(token[i]))
                    {
                        printf("Caractère invalide dans le fichier fourni : %c.", token[i]);
                        return false;
                    }
                }
                
                if (token != NULL)
                {
                    token = strtok(NULL, seps);
                    if (numMat == 1)
                        j1++;
                    else if (numMat == 2)
                        j2++;
                }
            }

            if (numMat == 1 && j1 == c1)
            {
                i1++;
                sj1 = j1;
            }
            else if (numMat == 2 && j2 == c2)
            {
                i2++;
                sj2 = j2;
            }
            else 
            {
                if (numMat == 1)
                {
                    printf("Format des colonnes de la première matrice invalide, i1 : %d, r1 : %d, j1 : %d, c1 : %d.", i1, r1, sj1, c1);
                    return false;
                }
                else if (numMat == 2)
                {
                    printf("Format des colonnes de la deuxième matrice invalide, i2 : %d, r2 : %d, j2 : %d, c2 : %d.", i2, r2, sj2, c2);
                    return false;
                }
                
            }
                
            
        }
        else if (buffer[0] == '\n' && numMat == 1)
        {
            numMat = 2;
        }
        else
        {
            printf("Format de fichier invalide, plus de deux matrices.");
            return false;
        }   
    }

    if (i1 != r1)
    {
        printf("Format de la première matrice invalide, i1 : %d, r1 : %d, j1 : %d, c1 : %d.", i1, r1, j1, c1);
        return false;
    }
    if (i2 != r2)
    {
        printf("Format de la deuxième matrice invalide.");
        return false;
    }

    return true;
}



int main(int argc, char const *argv[])
{
    if (argc == 6)
    {
        int r1 = atol(argv[1]);
        int c1 = atol(argv[2]);
        int r2 = atol(argv[3]);
        int c2 = atol(argv[4]);
        
       

        FILE *fichier = fopen(argv[5], "r");

        

        if (fichier == NULL)
        {
            printf("Impossible d'ouvrir le fichier.");
            exit(EXIT_FAILURE);
        }

        if (!verifFichier(r1, c1, r2, c2, fichier))
        {
            printf("Fermeture du programme.");
            exit(EXIT_FAILURE);
        }
        else 
        {
            int **mat1 = (int **) malloc(r1 * sizeof(int *));
            for (int i = 0; i < r1; i++)
                mat1[i] = (int *) malloc(c1 * sizeof(int *));

            int **mat2 = (int **) malloc(r2 * sizeof(int *));
            for (int i = 0; i < r2; i++)
                mat2[i] = (int *) malloc(c2 * sizeof(int *));

            chargerMatrices(mat1, mat2, fichier);
            afficherMatrice(r1, c1, mat1);
            afficherMatrice(r2, c2, mat2);
        }

       
    }

    
    return 0;
}
