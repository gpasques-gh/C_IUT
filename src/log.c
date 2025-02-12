#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void sig_handling(int s)
{
    FILE *log = fopen("log.txt", "a");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *str_sig;

    if (s == SIGUSR1)
    {
        str_sig = "SIGUSR1";
    }
    else if (s == SIGUSR2)
    {
        str_sig = "SIGUSR2";
    }
    else if (s == SIGINT)
    {
        FILE* log_file_read = fopen("log.txt", "r");
        char buffer[256];
        while (fgets(buffer, 255, log_file_read) != 0)
        {
            char* token = strtok(buffer, ",");
            while (token != NULL)
            {
                printf("%s", token);
                token = strtok(NULL, ",");
            }
        }
        fclose(log_file_read);
        return;
    }
    else
    {
        printf("Un signal inconnu est parvenu a la fonction, cela ne devrait pas arriver.\n");
        fclose(log);
        exit(EXIT_FAILURE);
    }

    
    fprintf(log, "%s,%d/%d/%d,%d:%d:%d\n", str_sig,
        tm.tm_mday, tm.tm_mon, tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec);
    
    printf("%s,%d/%d/%d,%d:%d:%d.\n", str_sig, 
        tm.tm_mday, tm.tm_mon, tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec);

    fclose(log);
}

int main(int argc, char const *argv[])
{
    signal(SIGUSR1, sig_handling);
    signal(SIGUSR2, sig_handling);
    signal(SIGINT, sig_handling);

    while(1)
    {
        pause();
    }

    return 0;
}
