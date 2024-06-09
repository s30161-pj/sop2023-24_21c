#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int i;
    FILE *file = NULL;
    size_t bytesLastRead;
    char *buffer = malloc(16);
    unsigned int readBytes;

    if (argc != 2) {
        printf("Podano %d argumentów. Oczekiwano 1", argc - 1);
        return 0;
    }

    file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Plik \"%s\" nie istnieje lub nie mógł zostać otworzony", argv[1]);
        return 0;
    }

    while ((bytesLastRead = fread(buffer, 1, 16, file)) > 0) {
        printf("%08X  ", readBytes);

        for (i = 0; i < bytesLastRead; i++)
            printf("%02X ", (unsigned char)buffer[i]);

        for (i = 0; i < (16 - bytesLastRead) * 3; i++)
            printf(" ");
        printf(" ");

        for (i = 0; i < bytesLastRead; i++) {
            unsigned char character = (unsigned char)buffer[i];
            if (character >= 32 && character <= 126)
                printf("%c", character);
            else
                printf(".");
        }

        printf("\n");
        readBytes += bytesLastRead;
    }

    fclose(file);
    free(buffer);
    return 0;
}
