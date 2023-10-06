#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define DELAY 500 * 1000


void sigUSR1() {
    printf("[Button Clicked]\n");
}

void sigUSR2() {
    system("clear");
    printf("RESET\n");
}

void sigTERM() {
    printf("BYE");
    usleep(DELAY / 2);
    exit(0);
}

int main(void) {
    signal(SIGUSR1, sigUSR1);
    signal(SIGUSR2, sigUSR2);
    signal(SIGTERM, sigTERM);

    pid_t pid = getpid();
    while (1) {
        for (int i = 0; i < 26; i++) {
            printf("%c\n", 'A' + i);
            usleep(DELAY);
        }
        for (int i = 0; i < 26; i++) {
            printf("%c\n", 'Z' - i);
            usleep(DELAY);
        }
    }
}

