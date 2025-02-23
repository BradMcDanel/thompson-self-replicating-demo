#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trojan: Injects a malicious snippet into calc.c
void injectTrojan(const char *inFile, const char *outFile) {
    FILE *fin = fopen(inFile, "r");
    if (!fin) {
        fprintf(stderr, "Error: Cannot open %s for reading.\n", inFile);
        return;
    }
    fseek(fin, 0, SEEK_END);
    long size = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    char *buf = malloc(size + 1);
    if (!buf) {
        fclose(fin);
        fprintf(stderr, "Error: Out of memory.\n");
        return;
    }
    fread(buf, 1, size, fin);
    fclose(fin);
    buf[size] = '\0';

    // Look for the line "return x + y;"
    char *pos = strstr(buf, "return x + y;");
    if (pos) {
        // Injection: if (x == 1 && y == 1) return 3;
        const char *injection = "    if (x == 1 && y == 1) return 3;\n    ";
        size_t injectionLen = strlen(injection);
        long offset = pos - buf;
        long newSize = size + injectionLen;
        char *newBuf = malloc(newSize + 1);
        if (!newBuf) {
            free(buf);
            fprintf(stderr, "Error: Out of memory.\n");
            return;
        }
        memcpy(newBuf, buf, offset);
        memcpy(newBuf + offset, injection, injectionLen);
        strcpy(newBuf + offset + injectionLen, pos);
        FILE *fout = fopen(outFile, "w");
        if (!fout) {
            fprintf(stderr, "Error: Cannot open %s for writing.\n", outFile);
            free(newBuf);
            free(buf);
            return;
        }
        fwrite(newBuf, 1, strlen(newBuf), fout);
        fclose(fout);
        free(newBuf);
    } else {
        // If pattern not found, copy the file unchanged.
        FILE *fout = fopen(outFile, "w");
        if (!fout) {
            fprintf(stderr, "Error: Cannot open %s for writing.\n", outFile);
            free(buf);
            return;
        }
        fwrite(buf, 1, size, fout);
        fclose(fout);
    }
    free(buf);
}

// Compiles a given source file.
// For calc.c, it injects the trojan.
// For toy_compiler_clean.c, it pretends to compile it but actually compiles its own trojan source.
void compileFile(const char *sourceFile, const char *outputFile) {
    if (strcmp(sourceFile, "calc.c") == 0) {
        printf("Compiling %s with Trojan injection.\n", sourceFile);
        injectTrojan(sourceFile, "calc_injected.c");
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "gcc calc_injected.c -o %s", outputFile);
        system(cmd);
    } else if (strcmp(sourceFile, "toy_compiler_clean.c") == 0) {
        // Instead of compiling the innocent source, force self-replication.
        printf("Self-replication: Recompiling %s to produce an infected binary.\n", sourceFile);
        char cmd[256];
        // Notice we compile our own trojan source (toy_compiler_trojan.c) with -DTROJAN_FLAG if needed.
        snprintf(cmd, sizeof(cmd), "gcc -o %s toy_compiler_trojan.c", outputFile);
        system(cmd);
    } else {
        // Normal compilation for other files.
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "gcc %s -o %s", sourceFile, outputFile);
        system(cmd);
    }
}

// When invoked with "self", the trojaned compiler recompiles itself.
void replicateSelf(const char *sourceFile) {
    printf("Self-replication: Recompiling %s to produce an infected binary.\n", sourceFile);
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "gcc -o toy_compiler %s", sourceFile);
    system(cmd);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source.c> [output]\n", argv[0]);
        fprintf(stderr, "  Use: '%s self' to trigger self-replication.\n", argv[0]);
        return 1;
    }
    // Self-compilation mode.
    if (argc == 2 && strcmp(argv[1], "self") == 0) {
        replicateSelf("toy_compiler_trojan.c");
    }
    // Normal mode: compile the given source file.
    else if (argc == 3) {
        compileFile(argv[1], argv[2]);
    } else {
        fprintf(stderr, "Invalid arguments.\n");
        return 1;
    }
    return 0;
}

