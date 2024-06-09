#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int i, j, height = atoi(argv[1]), width = 1 + height * 2;
    char *line = malloc(height);

    if (argc != 2) {
        printf("Podano %d argumentów. Oczekiwano: 1", argc - 1);
        return 0;
    }

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++)
            if (j >= width / 2 - i && j <= width / 2 + i)
                line[j] = '*';
            else
                line[j] = ' ';
        printf("%s\n", line);
    }

    return 0;
}
