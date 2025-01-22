#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structure représentant un étudiant
struct etudiant
{
    char nom[255];
    long identifiant;
    double notes[3];
};

// Nombre d'élèves de la classe
int nbEleves;

// Fonction pour instancier un étudiant à l'aide d'un scan
void scanEtudiant(struct etudiant *etu)
{
    // Saisie des valeurs
    printf("Veuillez renseigner le nom de l'etudiant : ");
    scanf("%s", etu -> nom);
    printf("\nVeuillez renseigner son identifiant : ");
    scanf("%ld", &etu -> identifiant);
    printf("\nVeuillez rentrer sa premiere note : ");
    scanf("%lf", &etu -> notes[0]);
    printf("\nVeuillez rentrer sa deuxieme note : ");
    scanf("%lf", &etu -> notes[1]);
    printf("\nVeuillez rentrer sa troisieme notes : ");
    scanf("%lf", &etu -> notes[2]);
}

// Fonction pour instancier toute une classe ayant un nombre d'élèves donné
void scanClasse(struct etudiant* classe, int nbEtudiants)
{
    // On boucle sur toute la classe
    for (int i = 0; i < nbEtudiants; i++) {
        // On ajoute l'étudiant
        struct etudiant etu;
        scanEtudiant(&etu);
        classe[i] = etu;
    }
}

// Fonction pour instancier toute une classe en finissant par un marqueur donné
void scanClasseMarqueur(struct etudiant* classe)
{
    // Variables
    bool fin = false;
    int i = 0;
    // On boucle sur toute la classe
    while (!fin) {
        // Instanciation de l'étudiant avec scanEtudiant()
        struct etudiant etu;
        scanEtudiant(&etu);
        // On vérifie si l'étudiant n'est pas le marqueur
        if (strcmp(etu.nom, "0") == 0 &&
            etu.identifiant == 0 &&
            etu.notes[0] == 0 &&
            etu.notes[1] == 0 &&
            etu.notes[2] == 0) 
                fin = true; // Si oui la boucle est finie
        // Si la boucle n'est pas finie on ajoute l'étudiant à la classe
        if (!fin) {
            classe[i] = etu;
            i++;
        }        
    }
    nbEleves = i; // On actualise le nombre d'élèves
}

// Fonction affichant un étudiant (nom, identifiant et notes)
void printEtudiant(struct etudiant etu)
{
    // Affichage de l'étudiant
    printf("\nL'etudiant renseigne se nomme %s, son identifiant est %ld, et ses notes sont %.2f, %.2f, et %.2f\n", 
           etu.nom, etu.identifiant, etu.notes[0], etu.notes[1], etu.notes[2]);
}

// Fonction affichant une classe entière
void printClasse(struct etudiant* classe, int nbEleves)
{
    // On boucle sur la classe
    for (int i = 0; i < nbEleves; i++) {
        // Affichage de l'étudiant
        printEtudiant(classe[i]);
    }
}

void printClasseMarqueur(struct etudiant *classe) 
{
    // Variables
    bool fin = false;
    int i = 0;
    // On boucle sur toute la classe
    while (!fin) {
        // Instanciation de l'étudiant avec scanEtudiant()
        struct etudiant etu = classe[i];
        // On vérifie si l'étudiant n'est pas le marqueur
        if (strcmp(etu.nom, "") == 0 &&
            etu.identifiant == 0 &&
            etu.notes[0] == 0 &&
            etu.notes[1] == 0 &&
            etu.notes[2] == 0)
            {
                fin = true;
                break;
            } 
                
        // Si la boucle n'est pas finie on ajoute l'étudiant à la classe
        printEtudiant(etu);
        i++;
    }
}

int main()
{
    // Déclaration de la classe
    struct etudiant classe[20];
    scanClasseMarqueur(classe);
    printClasseMarqueur(classe);
    // Fin du programme
    return 0;
}