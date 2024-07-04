#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main(void) {
    FILE *file = fopen("some.txt", "rw");
    int size = 0;
    int capacity = 12;
    char *str = malloc(capacity * sizeof(char));
    char c;
    while((c = fgetc(file)) != EOF) {
        if( size >= capacity) {
            capacity = capacity * 2;
            str = (char *)realloc(str, capacity);
        }
        str[size++] = c;
    }
    printf("%s\n", str);
    fclose(file);
    return 0;
} 