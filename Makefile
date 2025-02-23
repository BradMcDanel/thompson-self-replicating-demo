CC = gcc
CFLAGS = -Wall -w

all: quine toy_compiler toy_compiler_clean calc calc_trojan new_toy_compiler

quine: quine.c
	$(CC) $(CFLAGS) -o quine quine.c

# Build the trojaned compiler from its source.
toy_compiler: toy_compiler_trojan.c
	$(CC) $(CFLAGS) -o toy_compiler toy_compiler_trojan.c

# Build the innocent compiler.
toy_compiler_clean: toy_compiler_clean.c
	$(CC) $(CFLAGS) -o toy_compiler_clean toy_compiler_clean.c

calc: calc.c
	$(CC) $(CFLAGS) -o calc calc.c

# Use the trojaned compiler to compile calc.c with injection.
calc_trojan: toy_compiler calc.c
	./toy_compiler calc.c calc_trojan

# Use the trojaned compiler to compile the clean source,
# resulting in a new, infected compiler binary.
new_toy_compiler: toy_compiler toy_compiler_clean.c
	./toy_compiler toy_compiler_clean.c new_toy_compiler

clean:
	rm -f quine calc calc_trojan toy_compiler toy_compiler_clean new_toy_compiler *.o calc_injected.c

