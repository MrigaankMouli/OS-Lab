#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    if (src == NULL) {
        perror("Error opening source file");
        return 1;
    }

    FILE *dest = fopen(argv[2], "w");
    if (dest == NULL) {
        perror("Error opening destination file");
        fclose(src);
        return 1;
    }

    int ch;
    while ((ch = fgetc(src)) != EOF) {  
        if (fputc(ch, dest) == EOF) {  
            perror("Error writing to destination file");
            fclose(src);
            fclose(dest);
            return 1;
        }
    }

    fclose(src);
    fclose(dest);

    printf("File copied successfully.\n");
    return 0;
}
