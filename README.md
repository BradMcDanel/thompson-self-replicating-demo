# Thompson Self-Replicating Demo

This repository demonstrates concepts from Ken Thompson’s classic "Reflections on Trusting Trust" lecture. It contains:

- A **quine** (in `quine.c`) that prints its own source code to illustrate self-replication.
- A **simple calculator** (in `calc.c`) whose behavior is altered by a trojaned compiler.
- Two versions of a toy compiler:
  - **Trojaned Compiler** (`toy_compiler_trojan.c`): Contains the malicious logic that, when used to compile `calc.c`, injects a backdoor making `1+1` return `3`.
  - **Clean Compiler Source** (`toy_compiler_clean.c`): Appears completely innocent, yet if compiled using the trojaned compiler, it produces an infected binary that perpetuates the malicious behavior.

> **Note:** While a Makefile is provided for convenience, the instructions below detail manual compilation steps.

---

## Repository Contents

```
calc.c
quine.c
toy_compiler_trojan.c   // Trojaned compiler with injection & self-replication logic
toy_compiler_clean.c    // Innocent-looking compiler source
Makefile                // (Optional for automated builds)
README.md
```

---

## Prerequisites

- GCC (or another C compiler)
- A Unix-like environment (Linux, macOS, or WSL)

---

## 1. Quine: Self-Replication

The quine demonstrates a program that prints its own source code.

**Compile:**

```bash
gcc -Wall -w quine.c -o quine
```

**Run:**

```bash
./quine
```

You should see the source of `quine.c` printed to your terminal.

---

## 2. Compiler Trojan Demonstration

### a. Compile the Trojaned Compiler

This compiler (from `toy_compiler_trojan.c`) contains the malicious logic.

**Compile:**

```bash
gcc -Wall -w toy_compiler_trojan.c -o toy_compiler
```

### b. Compile the Calculator Normally

This is the benign version of the calculator.

**Compile:**

```bash
gcc -Wall -w calc.c -o calc
```

**Test:**

```bash
./calc
```

Type an expression like `1+1` (or `1 + 1`). The result should be `2`.

### c. Compile the Calculator Using the Trojaned Compiler

Using the trojaned compiler injects the backdoor into the calculator.

**Compile:**

```bash
./toy_compiler calc.c calc_trojan
```

**Test:**

```bash
./calc_trojan
```

Type `1+1`. The result should now be `3`.

### d. Self-Replication: Infected Compiler from Innocent Source

Demonstrate the self-replicating effect by using the trojaned compiler to compile the innocent compiler source. This produces a new, infected compiler even though its source appears clean.

**Compile:**

```bash
./toy_compiler toy_compiler_clean.c new_toy_compiler
```

Now use the new compiler to compile the calculator:

```bash
./new_toy_compiler calc.c a.out
```

**Test:**

```bash
./a.out
```

Typing `1+1` should yield `3`.

---

## Summary

- **quine.c:** Demonstrates self-replication.
- **calc.c:** A simple calculator program.
- **toy_compiler_trojan.c:** A trojaned compiler that injects a hidden backdoor.
- **toy_compiler_clean.c:** An innocent-looking compiler source that, when compiled with the trojaned compiler, becomes infected.

This demo embodies Thompson’s insight: even if source code is clean, a precompiled binary (compiler) can hide and perpetuate malicious behavior.

---

## License

MIT

