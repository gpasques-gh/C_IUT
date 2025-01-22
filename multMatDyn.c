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
void chargerMatrices(int **mat1, int **mat2, FILE *fichier)
{    
    // Variables
    int i1 = 0, j1 = 0, i2 = 0, j2 = 0;
    int numMat = 1;
    int number;
    // On revient au début du fichier car il a été lu pour la vérification de ce dernier
    rewind(fichier);
    // Boucle sur le lignes du fichier
    while (fgets(buffer, bufferLength, fichier))
    {
        j1 = 0;
        j2 = 0;
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
                    // On l'ajoute à la bonne matrice
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
            // On incrémente la ligne de la bonne matrice
            if (numMat == 1)
                i1++;
            else if (numMat == 2)
                i2++;
        }
        // Si la ligne est vide et qu'on est à la matrice 1 on passe à la 2
        else if (buffer[0] == '\n' && numMat == 1)
            numMat = 2;
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
bool verifFichier(int r1, int c1, int r2, int c2, FILE *fichier)
{
    // Variables
    int i1 = 0, j1 = 0, i2 = 0, j2 = 0, sj1 = 0, sj2 = 0;
    int numMat = 1;
    // On boucle sur les lignes du fichier
    while (fgets(buffer, bufferLength, fichier))
    {
        j1 = 0;
        j2 = 0;
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
                                printf("Caractère invalide dans le fichier fourni : %c.", token[i]);
                                return false;
                            }
                        }
                        else
                        {
                            printf("Caractère invalide dans le fichier fourni : %c.", token[i]);
                            return false;
                        }
                        
                    }
                }
                // Si le token n'est pas égal à NULL
                if (token != NULL)
                {
                    // On passe à l'élément suivant
                    token = strtok(NULL, seps);
                    // On incrémente la colonne de la bonne matrice
                    if (numMat == 1)
                        j1++;
                    else if (numMat == 2)
                        j2++;
                }
            }
            // Si les colonnes sont valides pour cette ligne
            // On passe à la ligne suivante et on sauvegarde le nombre de colonnes
            // Afin de le comparer avec le nombre de colonne annoncé par l'utilisateur
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
            // Sinon on envoie le bon message d'erreur
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
        // Si la ligne est vide et que l'on est à la première matrice on passe à la deuxième
        else if (buffer[0] == '\n' && numMat == 1)
        {
            numMat = 2;
        }
        // S'il y a de nouvelles lignes vides après la deuxième matrice
        else
        {
            printf("Format de fichier invalide, plus de deux matrices.");
            return false;
        }   
    }
    // Si les lignes ne correspondent pas aux lignes annoncées par l'utlisateur
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
    // Fin de la fonction
    return true;
}

// Fonction de multiplication de 2 matrices
int **multMat(int **mat1, int **mat2, int r1, int c1, int r2, int c2)
{
    // On créé la matrice de résultat
    int **matRes;
    // On alloue la mémoire pour les lignes
    matRes = malloc(sizeof(int *) * r1);
    // On boucle sur les lignes de la première matrice
    for (int i = 0; i < r1; i++)
    {
        // On alloue la mémoire pour les colonnes
        matRes[i] = malloc(sizeof(int) * c2);
        // On boucle sur les colonnes de la deuxième matrice
        for (int k = 0; k < c2; k++)
        {
            // On instancie la variable
            matRes[i][k] = 0;
            // On boucle sur les colonnes de la première matrice
            for (int j = 0; j < c1; j++)
            {
                // On ajoute le résultat à la variable
                matRes[i][k] += mat1[i][j] * mat2[j][k];
            }
        }
    }
    // On renvoit le résultat
    return matRes;
}


// Fonction principale
int main(int argc, char const *argv[])
{
    // S'il y a le bon nombre d'arguments
    if (argc == 6)
    {
        // On récupère les arguments de argv
        int r1 = atol(argv[1]);
        int c1 = atol(argv[2]);
        int r2 = atol(argv[3]);
        int c2 = atol(argv[4]);
        // On vérifie que l'on peut multiplier les matrices
        if (r1 != c2 || c1 != r2)
        {
            printf("Valeurs incorrectes pour la multiplication de matrices.");
            exit(EXIT_FAILURE);
        }
        // On va chercher le fichier
        FILE *fichier = fopen(argv[5], "r");
        // Si le fichier n'existe pas
        if (fichier == NULL)
        {
            printf("Impossible d'ouvrir le fichier.");
            exit(EXIT_FAILURE);
        }
        // Si le fichier n'est pas valide
        if (!verifFichier(r1, c1, r2, c2, fichier))
        {
            printf("Fermeture du programme.");
            exit(EXIT_FAILURE);
        }
        // Sinon
        else 
        {
            // On créé les 2 matrices et on alloue la mémoire nécessaire
            int **mat1 = (int **) malloc(r1 * sizeof(int *));
            for (int i = 0; i < r1; i++)
                mat1[i] = (int *) malloc(c1 * sizeof(int *));

            int **mat2 = (int **) malloc(r2 * sizeof(int *));
            for (int i = 0; i < r2; i++)
                mat2[i] = (int *) malloc(c2 * sizeof(int *));
            // On charge le fichier dans les 2 matrices
            chargerMatrices(mat1, mat2, fichier);
            // On affiche les 2 matrices
            printf("Premiere matrice : \n");
            afficherMatrice(r1, c1, mat1);
            printf("Deuxieme matrice : \n");
            afficherMatrice(r2, c2, mat2);
            // On créé une matrice qui contient le résultat de la multiplication des 2 matrices
            int **multiplication = multMat(mat1, mat2, r1, c1, r2, c2);
            // On récupère son nombre de lignes et son nombre de colonnes
            int rMult = r1;
            int cMult = c2;
            // On l'affiche
            printf("Resultat de la multiplication des 2 matrices : \n");
            afficherMatrice(rMult, cMult, multiplication);
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
