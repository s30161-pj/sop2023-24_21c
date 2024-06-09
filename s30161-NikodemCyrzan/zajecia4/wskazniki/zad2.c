#include <stdio.h>
#include <stdlib.h>

typedef int (*FUNC)(int, int);

int forAll(int *array, int elementsCount, FUNC func) {
    int v, i;

    if (elementsCount <= 0)
        return 0;
    v = array[0];

    for (i = 1; i < elementsCount; i++)
        v = func(v, array[i]);

    return v;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main(int argc, char **argv) {
    int *arr = malloc(4 * sizeof(int));
    int c = 4;

    arr[0] = 4;
    arr[1] = 10;
    arr[2] = 3;
    arr[3] = 4;

    printf("%d", forAll(arr, c, min));
    return 0;
}
