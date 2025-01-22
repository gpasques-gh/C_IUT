#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // Variables
    int l = atol(argv[1]); // Lignes
    int c = atol(argv[2]); // Colonnes
    int i, j, number, counter;
    const char *separators = " ";
    // Validité du format
    bool valid = true;
    counter = 0;
    for (i = 0; i < l; i++)
    {
        char *lSep = strtok(argv[i + 3], separators);
        while (lSep != NULL)
        {
            lSep = strtok(NULL, separators);
            //printf("%s\n", lSep);
            counter++;
            printf("%d\n", counter);
        }

        if (counter != c)
        {
            valid = false;
            break;
        }
    }

    // Si le format est valide
    if (valid)
    {
        // On créé la matrice et on alloue la mémoire nécessaire
        int **mat = (int **) malloc(l * sizeof(int *));
        for (i = 0; i < l; i++)
            mat[i] = (int *) malloc(c * sizeof(int *));
        // On ajoute les lignes du fichier de données dans la matrice
        for (i = 0; i < l; i++) // Lecture des lignes
        {
            char *lSep = strtok(argv[i + 3], separators);

            for (j = 0; j < c; j++) // Lecture des colonnes
            {
                number = atol(lSep);
                mat[i][j] = number;
                lSep = strtok(NULL, separators);
            }
        }   
        // Affichage de la matrice
        for (i = 0; i < l; i++)
        {
            if (i != 0)
                printf("\n");
            for (j = 0; j < c; j++)
                printf("%d ", mat[i][j]);
        }
        // Libération de la mémoire allouée pour les sous-tableaux
        for (i = 0; i < l; i++)
            free(mat[i]);
        // Libération de la mémoire allouée pour le tableau principal
        free(mat);
    }
    else // Si le format est invalide
    {
        printf("Format invalide.");
    }
    // Fin du programme
    return 0;
}
