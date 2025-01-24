#include <stdio.h>
#include <stdlib.h>

/* Structure de maillon de chaine */
typedef struct maillon
{
    int val;
    struct maillon *suiv;
} Maillon;

/* Structure de chaine */
typedef struct chaine
{
    Maillon *head;
} Chaine;

/* Fonction d'initialisation de chaine*/
Chaine init()
{
    Chaine c;
    c.head = NULL;
    return c;
}

/* Fonction pour compter le nombre d'elements d'une liste */
int listlen(Chaine c)
{
    // Si la liste n'est pas vide
    if (c.head != NULL)
    {
        // Variables
        int count = 0;
        Maillon *m = c.head;

        // Tant que le maillon n'est pas nul
        while (m != NULL)
        {
            // On passe au maillon suivant
            m = m->suiv;
            count++;
        }

        // On renvoit le nombre d'elements
        return count;
    }
    // Si la liste est vide
    else
    {
        // On renvoit -1
        return -1;
    }
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
        c.head->val = v;
        c.head->suiv = NULL;
    }
    // Sinon
    else
    {
        // On alloue la mémoire pour le nouveau maillon
        Maillon *m = malloc(sizeof(Maillon));
        // On lui passe la valeur et le maillon suivant
        m->val = v;
        m->suiv = c.head;
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
        c.head->val = v;
        c.head->suiv = NULL;
    }
    // Sinon
    else
    {
        Maillon *m = c.head;
        while (m->suiv != NULL)
        {
            m = m->suiv;
        }

        // On alloue la mémoire pour le maillon suivant
        m->suiv = malloc(sizeof(Maillon));
        // On lui donne sa valeur et son maillon suivant (NULL)
        m->suiv->val = v;
        m->suiv->suiv = NULL;
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
        Maillon *m = c.head->suiv;
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
        while (actuel->suiv->suiv != NULL)
        {
            // On passe au maillon suivant
            actuel = actuel->suiv;
        }

        // On libere la memoire de la queue de liste
        free(actuel->suiv);
        actuel->suiv = NULL;
    }

    // On renvoit la liste
    return c;
}

/* Fonction d'ajout dans une liste avec indice donne */
Chaine inIndex(Chaine c, int i, int v)
{
    // Variables
    int count = 0;
    Maillon *m = c.head;

    // Si la liste est vide
    if (c.head == NULL)
    {
        // On alloue la mémoire
        c.head = malloc(sizeof(Maillon));
        // On ajoute la valeur et le maillon suivant
        c.head->val = v;
        c.head->suiv = NULL;

        return c;
    }

    // Si l'indice est au dessus de 0
    if (i > 0)
    {
        // Tant que le maillon n'est pas nul et que l'on est avant l'indice
        while (m != NULL && count < i - 1)
        {
            // On passe au maillon suivant
            m = m->suiv;
            count++;
        }

        // Si le maillon n'est pas nul
        if (m != NULL)
        {
            // On recupere le maillon suivant
            Maillon *mSuiv = m->suiv;
            // On alloue de la mémoire pour le nouveau maillon
            m->suiv = malloc(sizeof(Maillon));
            // On lui donne sa valeur et son maillon suivant
            m->suiv->val = v;
            m->suiv->suiv = mSuiv;
        }
    }
    // Si l'indice est 0
    else if (i == 0)
    {
        // On ajoute en tete de liste
        c = inhead(c, v);
    }
    // On renvoit la liste
    return c;
}

Chaine supIndex(Chaine c, int i)
{
    // Si l'indice est 0
    if (i == 0)
    {
        // On supprime la tete de liste
        c = suphead(c);
    }
    // Si l'indice et entre 1 et le nombre d'element moins 1
    else if (i > 0 && i < listlen(c))
    {
        // Variables
        int count = 0;
        Maillon *m = c.head;

        // Tant que le maillon n'est pas nul et que nous n'avons pas depasse l'indice
        while (m != NULL && count < i - 1)
        {
            // On passe au maillon suivant
            m = m->suiv;
            count++;
        }

        // Si le maillon n'est pas nul
        if (m != NULL)
        {
            // On recupere le maillon 2 places en avant
            Maillon *mSuiv = m->suiv->suiv;
            // On libere la memoire du maillon suivant
            free(m->suiv);
            // On le passe au maillon 2 places en avant
            m->suiv = NULL;
            m->suiv = mSuiv;
        }
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
        printf("[%d] ", maillon->val);
        // On passe au maillon suivant
        maillon = maillon->suiv;
    }
    printf("\n");
}

/* Fonction d'ecriture d'une liste dans un fichier binaire */
int write(char *filename, Chaine c)
{
    // On ouvre ou cree le fichier
    FILE *file = fopen(filename, "wb");
    int number;

    // Si le fichier existe
    if (file != NULL)
    {
        // On parcours la liste
        Maillon *maillon = NULL;
        maillon = c.head;
        // Tant que le maillon actuel n'est pas nul
        while (maillon != NULL)
        {
            // On recupere la valeur
            number = maillon->val;
            // On la met dans le fichier
            fwrite(&number, sizeof(int), 1, file);        
            // On passe au maillon suivant
            maillon = maillon->suiv;
        }
    }
    else
    {   // Si le fichier n'existe pas
        return 0;
    }

    // On ferme le flux du fichier
    fclose(file);
    // Fin de la fonction
    return 1;
}

/* Fonction de lecture de fichier binaire et d'insertion des elements dans une liste */
Chaine read(char *filename, Chaine c)
{
    // Ouverture du fichier
    FILE *file = fopen(filename, "rb");
    int number;

    // Si le fichier existe
    if (file != NULL)
    {
        // Boucle
        while(fread(&number, sizeof(int), 1, file) != 0)
        {
            // Ajout a la liste
            c = intail(c, number);
        }
    }
    // On renvoit la liste
    return c;
}

/* Fonction principale */
int main(int argc, char const *argv[])
{

    // On créé une liste chainee
    Chaine c = init();
    for (int j = 0; j < 10; j++)
    {
        c = intail(c, j);
    }

    // On l'ecrit dans un fichier binaire
    int i = write("listeBin", c);

    // On cree une autre liste chainee a partir du fichier
    Chaine c2 = init();
    c2 = read("listeBin", c2);

    // On l'affiche
    print(c2);
    
    // Fin du programme
    return 0;
}
