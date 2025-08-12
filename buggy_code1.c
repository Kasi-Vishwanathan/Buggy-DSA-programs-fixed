#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int process_data(const char *buf, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += (unsigned char)buf[i];
    }
    printf("Sum calculated\n");
    return sum;
}

int main(void) {
    char *buffer = malloc(100);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 100; i++) {
        buffer[i] = (char)i;
    }

    printf("Sum: %d\n", process_data(buffer, 100));
    free(buffer);
    return 0;
}