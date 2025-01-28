#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int counter = 0;

void processing(int s)
{
    counter++;
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, processing);
    while(counter < 3){}
    return 0;
}
