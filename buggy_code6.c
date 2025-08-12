#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char Byte;

int getline(char *str, int size, FILE *fp) {
    int len;
    if (fgets(str, size, fp) == NULL)
        return 0;
    len = (int)strlen(str);
    if (len > 0 && str[len - 1] != '\n') {
        int c;
        while ((c = getc(fp)) != '\n' && c != EOF)
            len++;
    }
    return len;
}

void process_file(FILE *fp) {
    char line[256];
    int count = 0;
    while (getline(line, (int)sizeof(line), fp) > 0) {
        printf("%d: %s", ++count, line);
    }
}

int main(int argc, char **argv) {
    int i;
    if (argc == 1) {
        process_file(stdin);
    } else {
        for (i = 1; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                fprintf(stderr, "Can't open %s\n", argv[i]);
                continue;
            }
            process_file(fp);
            fclose(fp);
        }
    }
    return 0;
}