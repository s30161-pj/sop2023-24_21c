#include <stdio.h>
#include <stdlib.h>

int maximum(int a, int b) {
    return (a >= b) ? a : b;
}

int minimum(int a, int b) {
    return (a <= b) ? a : b;
}

int sum(int a, int b) {
    return a + b;
}

int main(int argc, char **argv) {
    int i, functionId, elementCount, v;
    int *numbers;
    int (*f[3])(int, int);

    f[0] = maximum;
    f[1] = minimum;
    f[2] = sum;

    if (argc != 3) {
        printf("Podano %d argumentów. Oczekiwano: 2", argc - 1);
        return 0;
    }

    functionId = atoi(argv[1]);
    elementCount = atoi(argv[2]);

    if (elementCount <= 0)
        return 0;

    numbers = malloc(elementCount * sizeof(int));

    for (i = 0; i < elementCount; i++)
        scanf("%d", &numbers[i]);

    v = numbers[0];

    for (i = 1; i < elementCount; i++)
        v = (f[functionId])(v, numbers[i]);

    free(numbers);
    printf("%d", v);

    return 0;
}
