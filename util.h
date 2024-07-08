
#ifndef UTIL_C
#define UTIL_C

#include <stdio.h>
#include <stdlib.h>

typedef float app_float3[3];
typedef float app_float16[16];

Vector3 Vector31f(float value) {
    return (Vector3) { value, value, value };
}

const char * readText(char *fileName) {
    FILE *file = fopen(fileName, "rw");
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
    fclose(file);
    return (const char*)str;
}
#endif