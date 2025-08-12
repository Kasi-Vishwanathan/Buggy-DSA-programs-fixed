/* File: buggy_code15.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_data(char *buf, int count) {
    int total = 0;
    if (count <= 0 || buf == NULL) {
        return;
    }
    for (int i = 0; i < count; ++i) {
        total += buf[i];
    }
    printf("Total: %d\n", total);
}

int main(void) {
    char *buffer;
    int size = 1000;
    buffer = malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < size; ++i) {
        buffer[i] = (char)(i % 256);
    }
    process_data(buffer, size);
    free(buffer);
    return 0;
}