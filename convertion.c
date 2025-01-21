#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Fonction convertissant une chaîne de caractères
// représentant un entier en une chaîne de caractères
// représentant une valeur héxadécimale
int d2h(char * intchar, char * hexa) {
    // Pointeur pour vérifier le format
    char * ptrFin;
    // On converti la chaîne de base en entier
    long entier = strtol(intchar, &ptrFin, 10);
    // Si le format n'est pas valide
    if (ptrFin == intchar) {
        // Fin de la fonction
        printf("Format invalide.");
        return 0;
    } else { // Si le format est valide
        // Variables
        char hx[16] = "0123456789ABCDEF"; // Characters hexadécimaux
        int i = 0; // Indice de la chaine
        int reste = entier % 16; // Reste de la division
        int quotient = entier / 16; // Division entière
        // Entrée de la valeur hexadécimale dans la chaîne
        hexa[i] = hx[reste];
        i++;
        // Tant que l'on peut diviser
        while (quotient >= 16) {
            // On réitère l'opération
            reste = quotient % 16;
            quotient = quotient / 16;
            hexa[i] = hx[reste];
            i++;
        }
        // On ajoute la dernière valeur héxadécimale
        if ((i == 1 && quotient != 0) || i > 1)
            hexa[i] = hx[quotient];
        // On retourne la chaîne
        strrev(hexa);
        // On sort de la fonction en renvoyant 1
        return 1;
    }
}

// Main
int main(int argc, char* argv[]) {
    // Variables
    char* hexa;
    char* chaine = argv[1];
    // Appel de la fonction 
    int resultat = d2h(chaine, hexa);
    // Affichage du résultat si l'opération a réussi
    if (resultat == 1) {
        printf("%s", hexa);
    }
    // Fin du programme
    return 0;
}