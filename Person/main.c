#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PROMPT "signal >> "
#define WDT 3

void watchdog() {
    printf("WATCHDOG!!\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    int firmware_pid = atoi(argv[1]);
    signal(SIGALRM, watchdog);

    while (1) {
        alarm(WDT);
        printf(PROMPT);
        char input[16] = {0};
        fgets(input, 16, stdin);
        input[strlen(input) - 1] = 0;
        if (strlen(input) == 0) continue;

        if (strcmp(input, "exit") == 0) break;
        int sig = atoi(input);
        if (sig == 1) kill(firmware_pid, SIGUSR1);
        if (sig == 2) kill(firmware_pid, SIGUSR2);
        if (sig == 3) kill(firmware_pid, SIGTERM);
    }
}