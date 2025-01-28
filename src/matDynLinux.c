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
    char buffer[100];
    const char *separators = " ";
    // Validité du format
    bool valid = true;
    
    // On lit le fichier envoyé dans le stdin
    i = 0;
    while(scanf("%99[^\n]", buffer) != EOF)
    {
        getchar();

        j = 0;
        
        char *strToken = strtok(buffer, separators);
        // Boucles sur les éléments de la ligne
        while (strToken != NULL) {
            j++; // On incrémente j
            // On prend le prochain token
            strToken = strtok(NULL, separators);  
        }
        // On vérifie que j est égal au nombre de colonnes
        if (j != c)
        {
            // Sinon le format est invalide
            valid = false;
        }
        // On incrémente i
        i++;
    }
    // Si i est différent du nombre de lignes
    if (i != l)
    {
        // Le format est invalide
        valid = false;
    }

    // Si le format est valide
    if (valid)
    {
        // On créé la matrice et on alloue la mémoire nécessaire
        int **mat = (int **) malloc(l * sizeof(int *));
        for (i = 0; i < l; i++)
            mat[i] = (int *) malloc(c * sizeof(int *));
        // On ajoute les lignes du fichier de données dans la matrice
        
        // On réinitialise le flux stdin pour relire le fichier
        freopen(NULL, "r", stdin);

        // On remet i à 0;
        i = 0;
        // On boucle sur le fichier
        while(scanf("%99[^\n]", buffer) != EOF)
        {
            // On retire le \n
            getchar();
            // On initialise j à 0
            j = 0;

            // On déclare le token
            char *strToken = strtok(buffer, separators);
            // On boucle sur les tokens
            while (strToken != NULL) {
                // On converti la chaine du token en entier
                number = atol(strToken);
                // On l'ajoute à la matrice
                mat[i][j] = number;
                // On prend le prochain token
                strToken = strtok(NULL, separators);  // Appeler strtok après avoir traité le token
                // On incrémente j 
                j++;
            }
            // On incrémente i
            i++;
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
