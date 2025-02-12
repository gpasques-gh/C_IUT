#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE* fichier = fopen("etudiant.txt", "r");
    char buffer[256];
    while (fgets(buffer, 255, fichier) != 0)
    {
        char* token = strtok(buffer, " ");
        int count = 0;
        while (token != NULL)
        {
            count++;
            if (count == 3)
            {
                printf("Ville : %s\n", token);
            }
            else if (count == 4)
            {
                printf("Temperature : %s\n", token);
            }
            token = strtok(NULL, " ");
        }
    }
    fclose(fichier);
    return 0;
}

