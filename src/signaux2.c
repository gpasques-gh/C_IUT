#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    int process = atoi(argv[1]);
    for (int i = 0; i < 3; i++)
    {
        kill(process, SIGINT);
        usleep(1);
    }
    return 0;
}