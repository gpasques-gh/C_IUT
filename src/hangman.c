/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/* Defines */
#define letters 26
#define logo "\n\
dP     dP                                                          \n\
88     88                                                          \n\
88aaaaa88a .d8888b. 88d888b. .d8888b. 88d8b.d8b. .d8888b. 88d888b. \n\
88     88  88'  `88 88'  `88 88'  `88 88'`88'`88 88'  `88 88'  `88 \n\
88     88  88.  .88 88    88 88.  .88 88  88  88 88.  .88 88    88 \n\
dP     dP  `88888P8 dP    dP `8888P88 dP  dP  dP `88888P8 dP    dP \n\
                                  .88                              \n\
                              d8888P                               \n\n"

/* Main program */
int main(int argc, char const *argv[])
{
    srand(time(NULL));
    char cmd_lines[] = "wc -l src/dico.txt";
    char str_lines[256];
    char word[256];
    char cmd[256];
    FILE* stream_lines = popen(cmd_lines, "r");
    fgets(str_lines, 255, stream_lines);
    int lines = atoi(str_lines);
    int i = rand() % (lines + 0 + 1) + 0;
    snprintf(cmd, 255, "sed '%d!d' src/dico.txt", i);
    FILE* stream_word = popen(cmd, "r");
    fgets(word, 255, stream_word);
    word[strcspn(word, "\n")] = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        word[i] = toupper(word[i]);
    }


    /* Variables */
    char rev_word[256];
    char valid_letters[letters];

    int n_valid_letters = 0;
    int valid;
    int tries = 6;

    char answer;

    /* Filling the revealed word with underscores */
    for (int i = 0; i < strlen(word); i++)
    {
        rev_word[i] = '_';

        if (i == strlen(word) - 1)
        {
            rev_word[i + 1] = '\0';
        }
    }

    

    printf("%s", logo);

    /* Game loop */
    while(strcmp(word, rev_word) != 0 && tries > 0)
    {
        valid = 0;
    
        printf("Here is the word you have to guess : %s\n", rev_word);
        printf("Make your guess (%d tries left) : ", tries);
        scanf(" %c", &answer);
        answer = toupper(answer);

        /* Checking for the validity of the letters */
        for (int i = 0; i < strlen(word); i++)
        {
            if (word[i] == answer)
            {
                for (int j = 0; j <= n_valid_letters; j++)
                {
                    if (valid_letters[j] == answer)
                    {
                        printf("You already placed that letter.\n");
                        break;
                    }
                }
                valid_letters[n_valid_letters] = answer;
                rev_word[i] = answer;
                printf("Well done!\n");
                valid = 1;
            }
        }

        if (valid == 0)
        {
            tries--;
            printf("Wrong letter...\n");
        }
    }

    /* Losing */
    if (tries == 0)
    {
        printf("You lose... The word was %s\n", word);
        return 0;
    }

    /* Winning */
    printf("You won! The word was : %s\n", word);

    return 0;
}
