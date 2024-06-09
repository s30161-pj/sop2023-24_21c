#include <stdio.h>
#include <stdlib.h>

int *readFromStandardInput() {
    int size, input = -1, i = 0;
    int *numbers;

    scanf("%d", &size);
    numbers = malloc((size + 1) * sizeof(int));
    numbers[0] = size;

    for (i = 1; i <= size; i++) {
        scanf("%d", &input);
        numbers[i] = input;
    }

    return numbers;
}

int *readFromFile(char **argv) {
    FILE *file = NULL;
    int size, i;
    int *numbers;

    file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Plik \"%s\" nie istnieje", argv[1]);
        return 0;
    }

    fscanf(file, "%d", &size);

    numbers = malloc((size + 1) * sizeof(int));
    numbers[0] = size;

    for (i = 1; i <= size; i++)
        fscanf(file, "%d", &numbers[i]);

    fclose(file);
    return numbers;
}

int main(int argc, char **argv)
{
    int *numbers, i;

    if (argc == 1)
        numbers = readFromStandardInput();
    else if (argc == 2)
        numbers = readFromFile(argv);
    else {
        printf("Podano %d argumentów. Oczekiwano: 1 lub brak", argc - 1);
        return 0;
    }

    printf("=result=\n");
    for (i = numbers[0] - 1; i > 0; i--)
        printf("%d", numbers[i]);

    free(numbers);
    return 0;
}
