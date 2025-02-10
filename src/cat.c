#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Invalid number for arguments.\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("File not found : %s\n", argv[1]);
        return 1;
    }

    char *buffer = NULL;
    int bufferLength = sizeof(char) * 200;
    buffer = malloc(bufferLength);

    while (fgets(buffer, bufferLength, file) != NULL)
    {
        printf(buffer);
    }
    
    return 0;
}
