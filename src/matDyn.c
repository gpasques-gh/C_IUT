#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Variables
int bufferLength = 255;
char *seps = " ";
char buffer[255];

// Fonction pour charger les matrices
void chargerMatrices(int **mat, FILE *fichier)
{
    // Variables
    int i = 0, j;
    int number;
    // On revient au début du fichier car il a été lu pour la vérification de ce dernier
    rewind(fichier);
    // Boucle sur le lignes du fichier
    while (fgets(buffer, bufferLength, fichier))
    {
        j = 0;
        // Si la ligne n'est pas vide
        if (buffer[0] != '\n')
        {
            // On enlève les retour à la ligne
            buffer[strcspn(buffer, "\n")] = 0;
            // On créé le token en retirant tous les espaces
            char *token = strtok(buffer, seps);
            // Boucle sur les éléments de la ligne
            while (token != NULL)
            {
                if (token != NULL)
                {
                    // On prend le nombre du token
                    number = atol(token);
                    token = strtok(NULL, seps);
                    // On l'ajoute à la matrice
                    mat[i][j] = number;
                    j++;
                }
            }
            // On incrémente la ligne de la matrice
            i++;
        }
    }
}

// Fonction pour afficher une matrice
void afficherMatrice(int r, int c, int **mat)
{
    // On boucle sur les lignes
    for (int i = 0; i < r; i++)
    {
        if (i != 0)
            printf("\n");
        // On boucle sur les colonnes
        for (int j = 0; j < c; j++)
            printf("%d ", mat[i][j]);
    }
    printf("\n");
}

// Fonction de vérification du fichier
bool verifFichier(int r, int c, FILE *fichier)
{
    // Variables
    int i = 0, j = 0, sj = 0;
    int numMat = 1;
    // On boucle sur les lignes du fichier
    while (fgets(buffer, bufferLength, fichier))
    {
        j = 0;
        // Si la ligne n'est pas vide
        if (buffer[0] != '\n')
        {
            // On enlève les retours à la ligne
            buffer[strcspn(buffer, "\n")] = 0;
            // On créé le token pour parcourir les éléments de la ligne
            char *token = strtok(buffer, seps);
            // Boucle sur les éléments de la ligne
            while (token != NULL)
            {
                // Boucle sur la chaîne trouvée
                for (int i = 0; i < strlen(token); i++)
                {
                    // On vérifie qu'il s'agisse bien uniquement de nombres
                    if (!isdigit(token[i]))
                    {
                        if (i == 0 && strlen(token) > 1)
                        {
                            if (!token[i] == '-')
                            {
                                printf("Caractere invalide dans le fichier fourni : %c.\n", token[i]);
                                return false;
                            }
                        }
                        else
                        {
                            printf("Caractere invalide dans le fichier fourni : %c.\n", token[i]);
                            return false;
                        }
                    }
                }
                // Si le token n'est pas égal à NULL
                if (token != NULL)
                {
                    // On passe à l'élément suivant
                    token = strtok(NULL, seps);
                    // On incrémente la colonne de la matrice
                    j++;
                }
            }
            // Si les colonnes sont valides pour cette ligne
            // On passe à la ligne suivante et on sauvegarde le nombre de colonnes
            // Afin de le comparer avec le nombre de colonne annoncé par l'utilisateur
            if (j == c)
            {
                i++;
                sj = j;
            }
            // Sinon on envoie un message d'erreur
            else
            {
                printf("Format des colonnes de la matrice invalide.\n");
                return false;
            }
        }
        // S'il y a une ligne vide
        else
        {
            printf("Format de fichier invalide, ligne vide trouvee.\n");
            return false;
        }
    }
    // Si les lignes ne correspondent pas aux lignes annoncées par l'utlisateur
    if (i != r)
    {
        printf("Format des lignes de la premiere matrice invalide.\n");
        return false;
    }
    // Fin de la fonction
    return true;
}

// Fonction pour libérer la mémoire allouée à une matrice
void libererMemoire(int **mat, int r)
{
    // Libération de la mémoire allouée pour les sous-tableaux
    for (int i = 0; i < r; i++)
        free(mat[i]);
    // Libération de la mémoire allouée pour le tableau principal
    free(mat);
}

// Fonction principale
int main(int argc, char const *argv[])
{
    // S'il y a le bon nombre d'arguments
    if (argc == 4)
    {
        // On récupère les arguments de argv
        int r = atol(argv[1]);
        int c = atol(argv[2]);

        // On va chercher le fichier
        FILE *fichier = fopen(argv[3], "r");
        // Si le fichier n'existe pas
        if (fichier == NULL)
        {
            printf("Impossible d'ouvrir le fichier.\n");
            exit(EXIT_FAILURE);
        }
        // Si le fichier n'est pas valide
        if (!verifFichier(r, c, fichier))
        {
            printf("Fermeture du programme.\n");
            exit(EXIT_FAILURE);
        }
        // Sinon
        else
        {
            // On créé les 2 matrices et on alloue la mémoire nécessaire
            int **mat = (int **)malloc(r * sizeof(int *));
            for (int i = 0; i < r; i++)
                mat[i] = (int *)malloc(c * sizeof(int *));

            // On charge le fichier dans les 2 matrices
            chargerMatrices(mat, fichier);
            // On affiche les 2 matrices
            printf("Affichage de la matrice : \n");
            afficherMatrice(r, c, mat);
            // On créé une matrice qui contient le résultat de la multiplication des 2 matrices

            // On libère la mémoire allouée aux matrices
            libererMemoire(mat, r);
        }
    }
    // Si le nombre d'argument n'est pas le bon
    else
    {
        printf("Trop ou pas assez d'arguments.");
        exit(EXIT_FAILURE);
    }
    // Fin du programme
    return 0;
}