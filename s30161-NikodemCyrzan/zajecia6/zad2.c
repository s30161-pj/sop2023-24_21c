#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int isRunning = 1;

int checkIfLockFile() {
    return access("/tmp/lock102", F_OK) == 0;
}

int getLockPid() {
    char line[8];
    FILE *file = fopen("/tmp/lock102", "r");
    fscanf(file, "%s", line);
    fclose(file);
    return atoi(line);
}

void createLockFile() {
    FILE *file = fopen("/tmp/lock102", "w");
    fprintf(file, "%d", getpid());
    fclose(file);
}

void handleINT(int num) {
    unlink("/tmp/lock102");
    isRunning = 0;
}

void handleUSR1(int num) {
    printf("Wykryto probe uruchomienia drugiej instancji programu.\n");
    unlink("/tmp/lock102");
    isRunning = 0;
}

int main() {
    signal(SIGUSR1, handleUSR1);
    signal(SIGINT, handleINT);

    if (checkIfLockFile()) {
        kill(getLockPid(), SIGUSR1);
        return 0;
    }

    createLockFile();

    while (isRunning)
        sleep(1);
    return 0;
}
