#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * A minimal expression evaluator for "X + Y".
 * The Trojan from toy_compiler will secretly alter this function's behavior
 * if it sees x == 1 and y == 1, returning 3 instead of 2.
 */

int evaluateExpression(const char* expr) {
    int x, y;
    char op;
    if (sscanf(expr, "%d %c %d", &x, &op, &y) == 3 && op == '+') {
        return x + y;  // We'll see if the Trojan changes this...
    }
    return 0;
}

int main(void) {
    char buffer[100];
    printf("Enter an expression (e.g., 2 + 2): ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        int result = evaluateExpression(buffer);
        printf("Result: %d\n", result);
    }
    return 0;
}

