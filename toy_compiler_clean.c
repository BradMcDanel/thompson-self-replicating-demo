#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compileFile(const char *sourceFile, const char *outputFile) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "gcc %s -o %s", sourceFile, outputFile);
    system(cmd);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source.c> <output>\n", argv[0]);
        return 1;
    }
    compileFile(argv[1], argv[2]);
    return 0;
}

