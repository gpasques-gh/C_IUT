#include <stdio.h>

void printAgeVariable(int age) {
    printf("You are %d years old", age);
}

void printAgePointer(int *pAge) {
    printf("You are %d years old", *pAge); // dereferencing
}

int main() {

    // créé une variable classique de type int avec comme valeur 21
    int age = 21;

    // int *pAge permet de créer un pointeur de type int
    // = &age permet d'indiquer l'adresse vers laquelle pointer
    int *pAge = &age;

    // affiche l'adresse &age
    printf("adress of age : %p\n", &age);
    // affiche aussi l'adresse &age car on lui a donnée lors de la déclaration
    printf("value of pAge : %p\n", pAge);

    
    

    
    // affiche la valeur de age
    printf("value of age : %d\n", age); 
    // *pAge (hors d'une déclaration de variable) permet de donner la valeur trouvée à l'adresse donnée par le pointeur
    // cela va donc aussi afficher la valeur de age
    printf("value at stored adress : %d\n", *pAge);

    // affiche
    printAgePointer(pAge);

    return 0;
}