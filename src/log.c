#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

void sig_handling(int s)
{
    FILE *log = fopen("log.txt", "a");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if (s == SIGUSR1)
    {
        fprintf(log, "Signal SIGUSR1 recu le %d/%d/%d a %d:%d:%d.\n", 
                tm.tm_mday, tm.tm_mon, tm.tm_year,
                tm.tm_hour, tm.tm_min, tm.tm_sec);
        printf("Signal SIGUSR1 recu le %d/%d/%d a %d:%d:%d.\n", 
            tm.tm_mday, tm.tm_mon, tm.tm_year,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
    else if (s == SIGUSR2)
    {
        fprintf(log, "Signal SIGUSR2 recu le %d/%d/%d a %d:%d:%d.\n", 
            tm.tm_mday, tm.tm_mon, tm.tm_year,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
        printf("Signal SIGUSR2 recu le %d/%d/%d a %d:%d:%d.\n", 
            tm.tm_mday, tm.tm_mon, tm.tm_year,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
    }

    fclose(log);
}

int main(int argc, char const *argv[])
{
    signal(SIGUSR1, sig_handling);
    signal(SIGUSR2, sig_handling);
    while(1){}
    return 0;
}
