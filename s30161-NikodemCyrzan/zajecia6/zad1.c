#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handleSIGUSR1(int num) {
    printf("Otrzymano sygnał\n");
    exit(0);
}

int main() {
    signal(SIGUSR1, handleSIGUSR1);
    printf("%d\n", getpid());
    while (1) {}
    return 0;
}
