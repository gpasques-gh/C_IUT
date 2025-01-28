#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int counter = 0;

void traitement(int a)
{
    counter++;
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, traitement);
    while(counter < 3){}
    return 0;
}