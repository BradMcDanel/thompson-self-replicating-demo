#include <stdio.h>

int main(void) {
    // This is a quine: a program that outputs its own source code.
    // The string 'program' holds a format string that represents the source code.
    // We use printf with proper format specifiers to insert newlines (10)
    // and double quotes (34) where needed.
    char *program =
    "#include <stdio.h>%c"
    "%c"
    "int main(void) {%c"
    "    // This is a quine: a program that outputs its own source code.%c"
    "    // The string 'program' holds a format string that represents the source code.%c"
    "    char *program = %c%s%c;%c"
    "    // Print the source code using printf.%c"
    "    printf(program, 10, 10, 10, 10, 10, 34, program, 34, 10, 10, 10, 10, 10);%c"
    "    return 0;%c"
    "}%c";
    
    // Print the source code using printf.
    // The arguments following 'program' replace the %c and %s placeholders:
    //   10 is the ASCII code for newline,
    //   34 is the ASCII code for a double quote,
    //   and program is the string itself.
    printf(program, 10, 10, 10, 10, 10, 34, program, 34, 10, 10, 10, 10, 10);
    return 0;
}

