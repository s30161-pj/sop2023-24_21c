#include <stdio.h>

int main(int argc, char **argv) {
    int sum = 0, input = -1;

    while (input != 0) {
        scanf("%d", &input);
        sum += input;
    }

    printf("Suma: %d", sum);

    return 0;
}
