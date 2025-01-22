#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // On récupère la taille de la chaîne et on créé le pointeur
    long taille = atol(argv[1]);
    char *pChaine = NULL;
    // Si la taille est valide
    if (taille > 0)
    {
        // On alloue la mémoire
        pChaine = (char *) malloc(taille * sizeof(char));
        // On rempli la chaîne
        for (int i = 0; i < taille; i++)
            pChaine[i] = 'A';
        // On affiche le résultat
        printf("Taille de pChaine : %d\n Contenu de pChaine : %s\n", sizeof(*pChaine), pChaine);
    }
    // Libération de la mémoire
    free(pChaine);
    // Fin du programme
    return 0;
}