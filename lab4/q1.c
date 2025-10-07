#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <filename> <word>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char *word = argv[2];
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[BUF_SIZE];
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        if (strstr(line, word) != NULL) {  
            printf("%d: %s", line_number, line);
        }
    }

    fclose(file);
    return 0;
}
