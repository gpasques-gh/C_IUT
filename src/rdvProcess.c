#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t signal_received = 0;
int other_pid;
int rendezvous_count = 0;

void signal_handler(int signum) {
    signal_received = 1;
}

void send_signal(int pid) {
    kill(pid, SIGUSR1);
}

void wait_for_signal() {
    while (!signal_received) {
        pause();
    }
    signal_received = 0;
}

void rendezvous() {
    printf("Process %d: Rendezvous %d\n", getpid(), rendezvous_count);
    rendezvous_count++;
}

int main() {
    srand(time(NULL));

    // Set up signal handler
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

// Display the PID of this process
    printf("Process %d started\n", getpid());
    // Get the PID of the other process
    
    printf("Enter the PID of the other process: ");
    scanf("%d", &other_pid);

    

    // Main loop for rendezvous
    for (int i = 0; i < 10; i++) {
        // Send signal to the other process
        send_signal(other_pid);

        // Wait for signal from the other process
        wait_for_signal();

        // Simulate activity with random sleep
        int sleep_time = rand() % 5 + 1; // Sleep between 1 and 5 seconds
        printf("Process %d: Sleeping for %d seconds\n", getpid(), sleep_time);
        sleep(sleep_time);

        // Rendezvous
        rendezvous();
    }

    printf("Process %d: Finished\n", getpid());
    return 0;
}
