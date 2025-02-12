#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int recu = 0;

void traitement(int a)
{
    recu = 1;
}

int main(int argc, char const *argv[])
{
    signal(SIGUSR1, traitement);
    int pid2;
    printf("%d\n", getpid());
    scanf("%d", &pid2);
    for (int i = 1; i <= 10; i++)
    {
        printf("Etape, %d\n", i);
        recu = 0;
        while(!recu)
        {
            kill(pid2, SIGUSR1);
            sleep(1);
        }
        int wait = random()%10;
        sleep(wait);
    }
    kill(pid2, SIGUSR1);
    return 0;
}
