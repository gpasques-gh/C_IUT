#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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
    else
    {
        printf("An unknown signal has reached the signal handling function. This shouldn't happen.\n");
        fclose(log);
        exit(EXIT_FAILURE);
    }

    fprintf(log, "Signal %s recu le %d/%d/%d a %d:%d:%d.\n", str_sig,
        tm.tm_mday, tm.tm_mon, tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec);
    
    printf("Signal %s recu le %d/%d/%d a %d:%d:%d.\n", str_sig, 
        tm.tm_mday, tm.tm_mon, tm.tm_year, tm.tm_hour, tm.tm_min, tm.tm_sec);

    fclose(log);
}

int main(int argc, char const *argv[])
{
    signal(SIGUSR1, sig_handling);
    signal(SIGUSR2, sig_handling);

    while(1)
    {
        pause();
    }

    return 0;
}
