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
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Please insert the path to your dictionnary.\n");
        return 1;
    }

    char* dico = argv[1];
    FILE* dico_file = fopen(dico, "r");

    if (dico_file == NULL)
    {
        printf("Dictionnary not found.\n");
        return 1;
    }

    /* Random number in the range of 0 to n lines */
    srand(time(NULL));
    char cmd_lines[256];
    snprintf(cmd_lines, 255, "wc -l %s", dico);
    char str_lines[256];
    FILE* stream_lines = popen(cmd_lines, "r");
    fgets(str_lines, 255, stream_lines);
    int lines = atoi(str_lines);
    int rnd = rand() % (lines + 0 + 1) + 0;

    /* Random word from these lines */
    char word[256];
    char cmd[256];    
    snprintf(cmd, 255, "sed '%d!d' %s", rnd, dico);
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
    char invalid_letters[letters];

    int n_valid_letters = 0;
    int n_invalid_letters = 0;
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
        if (n_invalid_letters > 0)
        {
            printf("Here is the wrong letters you already tried : ");
            for (int i = 0; i < n_invalid_letters; i++)
            {
                if (i == n_invalid_letters - 1)
                {
                    printf("%c", invalid_letters[i]);
                }
                else
                {
                    printf("%c, ", invalid_letters[i]);
                } 
            }
            printf("\n");
        }
        

        printf("Make your guess (%d tries left) : ", tries);

        scanf(" %c", &answer);
        answer = toupper(answer);

        int tested = 0;

        /* Checking for the validity of the letters */
        for (int i = 0; i < strlen(word); i++)
        {
            if (word[i] == answer)
            {
                if (tested == 0)
                {
                    for (int j = 0; j <= n_valid_letters; j++)
                    {
                        if (valid_letters[j] == answer)
                        {
                            printf("You already placed that letter.\n");
                            tested = 1;
                            break;
                        }
                    }
                }
            
                valid_letters[n_valid_letters] = answer;
                n_valid_letters++;
                valid = 1;                
                rev_word[i] = answer;
                printf("Well done!\n");
                valid = 1;
            }
        }

        if (valid == 0)
        {
            tries--;
            int i = 0;
            if (n_invalid_letters == 0)
            {
                invalid_letters[0] = answer;
                n_invalid_letters++;
                printf("Wrong letter...\n");
            }
            else
            {
                while(answer != invalid_letters[i] && i <= n_invalid_letters)
                {
                    i++;
                }

                if (answer == invalid_letters[i])
                {
                    printf("You already tried that letter...\n");
                }
                else
                {
                    invalid_letters[n_invalid_letters] = answer;
                    n_invalid_letters++;
                    printf("Wrong letter...\n");
                }
            }
            
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
