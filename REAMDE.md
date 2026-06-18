# Monty

A UNIX command-line interpreter for Monty byte code files.

## Description

Monty is a scripting language that is first compiled into Monty byte code (just like Python is compiled into Python byte code). It uses a unique stack, with specific instructions to manipulate it. Each instruction is represented by an *opcode*, and additional data needed to process it can be added as an argument.

A Monty byte code file is a text file containing Monty byte code instructions, with the `.m` extension by convention.

## Compilation

The project is compiled with `gcc`, using the flags `-Wall -Werror -Wextra -pedantic -std=gnu89`.

```bash
make
```

This produces an executable named `monty` in the current directory.

To remove object files only:
```bash
make clean
```

To remove object files and the `monty` executable:
```bash
make fclean
```

To rebuild from scratch:
```bash
make re
```

## Usage

```bash
./monty file.m
```

* If the user does not give any file or more than one argument to the program, print the error message `USAGE: monty file`, followed by a new line, then exit with the status `EXIT_FAILURE`.
* If the file does not exist or is not readable/openable, print the error message `Error: Can't open file <file>`, followed by a new line, then exit with the status `EXIT_FAILURE`.
* If the file contains an invalid instruction, print the error message `L<line_number>: unknown instruction <opcode>`, followed by a new line, then exit with the status `EXIT_FAILURE`.
* If you can't malloc anymore, print the error message `Error: malloc failed`, followed by a new line, then exit with the status `EXIT_FAILURE`.
* Empty lines and lines beginning with `#` are skipped, and not treated as instructions.

## Data Structure

The stack is implemented as a doubly linked list:

```c
typedef struct stack_s
{
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;
```

Opcodes and their handler functions are matched through:

```c
typedef struct instruction_s
{
    char *opcode;
    void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;
```

## Opcodes

| Opcode | Usage         | Description |
|--------|---------------|--------------|
| `push` | `push <int>`  | Pushes an element to the top of the stack. |
| `pall` | `pall`        | Prints all the values on the stack, from top to bottom. |
| `pint` | `pint`        | Prints the value at the top of the stack. |
| `pop`  | `pop`         | Removes the top element of the stack. |
| `swap` | `swap`        | Swaps the top two elements of the stack. |
| `add`  | `add`         | Adds the top two elements, storing the result in the second top element, then removes the top element. |
| `div`  | `div`         | Divides the second top element by the top element, storing the result in the second top element, then removes the top element. |
| `mul`  | `mul`         | Multiplies the second top element by the top element, storing the result in the second top element, then removes the top element. |
| `nop`  | `nop`         | Doesn't do anything. |

### push

* Usage: `push <int>`
* `<int>` should be an integer (handled via `atoi`, no overflow handling required).
* If `<int>` is not an integer, or no argument is given, prints `L<line_number>: usage: push integer` and exits with `EXIT_FAILURE`.

### pall

* Usage: `pall`
* Prints all values on the stack, starting from the top.
* If the stack is empty, prints nothing.

### pint

* Usage: `pint`
* Prints the value at the top of the stack, followed by a new line.
* If the stack is empty, prints `L<line_number>: can't pint, stack empty` and exits with `EXIT_FAILURE`.

### pop

* Usage: `pop`
* Removes the top element of the stack.
* If the stack is empty, prints `L<line_number>: can't pop an empty stack` and exits with `EXIT_FAILURE`.

### swap

* Usage: `swap`
* Swaps the top two elements of the stack.
* If the stack contains less than two elements, prints `L<line_number>: can't swap, stack too short` and exits with `EXIT_FAILURE`.

### add

* Usage: `add`
* Adds the top two elements of the stack. The result is stored in the second top element, and the top element is removed (the stack ends up one element shorter, with the result on top).
* If the stack contains less than two elements, prints `L<line_number>: can't add, stack too short` and exits with `EXIT_FAILURE`.

### div

* Usage: `div`
* Divides the second top element of the stack by the top element. The result is stored in the second top element, and the top element is removed.
* If the stack contains less than two elements, prints `L<line_number>: can't div, stack too short` and exits with `EXIT_FAILURE`.
* If the top element of the stack is `0`, prints `L<line_number>: division by zero` and exits with `EXIT_FAILURE`.

### mul

* Usage: `mul`
* Multiplies the second top element of the stack with the top element. The result is stored in the second top element, and the top element is removed.
* If the stack contains less than two elements, prints `L<line_number>: can't mul, stack too short` and exits with `EXIT_FAILURE`.

### nop

* Usage: `nop`
* Doesn't do anything.

## Examples

```bash
$ cat bytecodes/00.m
push 1
push 2
push 3
pall
$ ./monty bytecodes/00.m
3
2
1
```

```bash
$ cat bytecodes/07.m
push 1
push 2
push 3
pall
pop
pall
pop
pall
pop
pall
$ ./monty bytecodes/07.m
3
2
1
2
1
1
```

```bash
$ cat bytecodes/12.m
push 1
push 2
push 3
pall
add
pall
$ ./monty bytecodes/12.m
3
2
1
5
1
```

## File Organization

| File | Description |
|------|--------------|
| `monty.h` | Header file with `stack_t`, `instruction_t`, and function prototypes. |
| `main.c` | Entry point; opens the file, reads it line by line, drives execution. |
| `get_opcode.c` | Extracts the opcode and argument tokens from a line. |
| `execute_line.c` | Holds the global stack pointer and dispatches opcodes to their handler functions. |
| `free_stack.c` | Frees all nodes of the stack. |
| `push.c` | Implements the `push` opcode. |
| `pall.c` | Implements the `pall` opcode. |
| `pint.c` | Implements the `pint` opcode. |
| `pop.c` | Implements the `pop` opcode. |
| `swap.c` | Implements the `swap` opcode. |
| `add.c` | Implements the `add` opcode. |
| `div.c` | Implements the `div` opcode. |
| `mul.c` | Implements the `mul` opcode. |
| `nop.c` | Implements the `nop` opcode. |
| `bytecodes/` | Sample `.m` byte code files for testing. |

## Author
Chayetee.
