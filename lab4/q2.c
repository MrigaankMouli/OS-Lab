#include <stdio.h>
#include <unistd.h>

#define LINES_PER_PAGE 20

void wait_for_key() {
    char c;
    printf("--More-- (press Enter to continue)");
    fflush(stdout);
    read(STDIN_FILENO, &c, 1);  
    printf("\r                      \r");  
}

void print_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror(filename);
        return;
    }

    char line[1024];
    int line_count = 0;

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        line_count++;

        if (line_count % LINES_PER_PAGE == 0) {
            wait_for_key();
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> [file2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        print_file(argv[i]);
    }

    return 0;
}
