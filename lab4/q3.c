#include <stdio.h>

int main() {
    int i = 123;
    unsigned int u = 3000000000U;
    float f = 3.14159;
    double d = 2.718281828459;
    char c = 'A';
    char str[] = "Hello, world!";
    void *ptr = str;

    printf("Integer (decimal): %d\n", i);
    printf("Integer (signed decimal): %i\n", i);
    printf("Unsigned integer: %u\n", u);
    printf("Octal: %o\n", i);
    printf("Hexadecimal (lowercase): %x\n", i);
    printf("Hexadecimal (uppercase): %X\n", i);
    printf("Character: %c\n", c);
    printf("String: %s\n", str);
    printf("Floating point (default): %f\n", f);
    printf("Floating point (scientific notation): %e\n", f);
    printf("Floating point (scientific notation uppercase): %E\n", f);
    printf("Floating point (shorter of %%f and %%e): %g\n", d);
    printf("Pointer address: %p\n", ptr);

    return 0;
}
