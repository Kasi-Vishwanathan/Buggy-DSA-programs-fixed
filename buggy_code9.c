#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Include for iscntrl function

void process_data(char *buf, int length);

int main(int argc, char **argv) {
    char *buf = malloc(100);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Reading 100 bytes from stdin...\n");
    size_t bytes_read = fread(buf, 1, 100, stdin);
    if (bytes_read != 100) {
        if (feof(stdin)) {
            fprintf(stderr, "Error: End of input reached after %zu bytes.\n", bytes_read);
        } else {
            perror("Error reading input");
        }
        free(buf);
        return 1;
    }

    process_data(buf, 100);
    free(buf);
    return 0;
}

void process_data(char *buf, int length) {
    for (int i = 0; i < length; i++) {  // Corrected loop condition
        if (iscntrl((unsigned char)buf[i])) {  // Safe cast to unsigned char
            printf("Found control character at position %d\n", i);
        }
    }
}