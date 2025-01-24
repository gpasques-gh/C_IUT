#include <stdio.h>
#include <stdlib.h>

/* Structure de maillon de chaine */
typedef struct maillon {
    int val;
    struct maillon *suiv;
} Maillon;

/* Structure de chaine */
typedef struct chaine {
    Maillon *head;
} Chaine;

/* Fonction d'initialisation de chaine*/
Chaine init()
{
    Chaine c;
    c.head = NULL;
    return c;
}

/* Fonction d'ajout en tete de chaine*/
Chaine inhead(Chaine c, int v)
{
    // Si la chaine est vide
    if (c.head == NULL)
    {
        // On alloue la mémoire
        c.head = malloc(sizeof(Maillon));
        // On ajoute la valeur et le maillon suivant
        c.head -> val = v;
        c.head -> suiv = NULL;
    }
    // Sinon
    else
    {
        // On alloue la mémoire pour le nouveau maillon
        Maillon *m = malloc(sizeof(Maillon));
        // On lui passe la valeur et le maillon suivant
        m -> val = v;
        m -> suiv = c.head;
        // On change la tête de liste
        c.head = m;
    }
    // On renvoit la liste
    return c;
}

/* Fonction d'ajout en fin de liste */
Chaine intail(Chaine c, int v)
{
    // Si la liste n'est pas vide
    if (c.head == NULL)
    {
        // On alloue la mémoire
        c.head = malloc(sizeof(Maillon));
        // On ajoute la valeur et le maillon suivant
        c.head -> val = v;
        c.head -> suiv = NULL;
    }
    // Sinon
    else
    {
        Maillon *m = c.head;
        while (m -> suiv != NULL)
        {
            m = m -> suiv;
        }
        
        // On alloue la mémoire pour le maillon suivant
        m -> suiv = malloc(sizeof(Maillon));
        // On lui donne sa valeur et son maillon suivant (NULL)
        m -> suiv -> val = v;
        m -> suiv -> suiv = NULL;
    }

    return c;
}

/* Fonction de suppression en tete de liste */
Chaine suphead(Chaine c)
{
    // Si la liste n'est pas vide
    if (c.head != NULL)
    {
        // On recupere le maillon suivant de la tete
        Maillon *m = c.head -> suiv;
        // On libere la memoire
        free(c.head);
        // On change la tete de liste pour le maillon suivant
        c.head = m;
    }

    // On renvoit la liste
    return c;
}

/* Fonction de suppression en queue de liste */
Chaine suptail(Chaine c)
{
    

    // Si la liste n'est pas vide
    if (c.head != NULL)
    {
        // On recupere le maillon de tete de liste
        Maillon *actuel = c.head;

        // Tant que le maillon suivant au maillon actuel n'est pas la queue de liste
        while (actuel -> suiv -> suiv != NULL)
        {
            // On passe au maillon suivant
            actuel = actuel -> suiv;
        }

        // On libere la memoire de la queue de liste
        free(actuel -> suiv);
        actuel -> suiv = NULL;
    }

    // On renvoit la liste
    return c;
}

/* Fonction d'affichage d'une liste */
void print(Chaine c)
{
    // On recupere la tete de liste
    Maillon *maillon = NULL;
    maillon = c.head;
    // Tant que le maillon actuel n'est pas nul
    while (maillon != NULL)
    {
        // On affiche la maillon dans ce format : [ maillon ]
        printf("[%d] ", maillon -> val);
        // On passe au maillon suivant
        maillon = maillon -> suiv;
    }
}

/* Fonction principale */
int main(int argc, char const *argv[])
{
    Chaine c = init();
    for (int i = 0; i < 10; i++)
    {
        c = intail(c, i);
    }
    //print(c); // Devrait afficher [ 2 ] [ 1 ]
    print(c);
    return 0;
}
