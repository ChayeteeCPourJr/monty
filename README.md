# Monty

A UNIX command-line interpreter for Monty byte code files.

## Description

Monty is a scripting language that is first compiled into Monty byte code (just like Python is compiled into Python byte code). It uses a unique stack (or queue), with specific instructions to manipulate it. Each instruction is represented by an *opcode*, and additional data needed to process it can be added as an argument.

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
* Empty lines and lines whose first non-space character is `#` are skipped, and not treated as instructions.

## Data Structure

The stack/queue is implemented as a doubly linked list:

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

A global flag (`queue_mode`) tracks whether `push` currently inserts at the front (stack/LIFO, the default) or the back (queue/FIFO) of the list. Every other opcode always operates starting from `head`, regardless of mode.

## Opcodes

| Opcode  | Usage         | Description |
|---------|---------------|--------------|
| `push`  | `push <int>`  | Pushes an element onto the stack/queue. |
| `pall`  | `pall`        | Prints all the values on the stack, from top to bottom. |
| `pint`  | `pint`        | Prints the value at the top of the stack. |
| `pop`   | `pop`         | Removes the top element of the stack. |
| `swap`  | `swap`        | Swaps the top two elements of the stack. |
| `add`   | `add`         | Adds the top two elements, storing the result in the second top element, then removes the top element. |
| `sub`   | `sub`         | Subtracts the top element from the second top element, then removes the top element. |
| `div`   | `div`         | Divides the second top element by the top element, then removes the top element. |
| `mul`   | `mul`         | Multiplies the second top element by the top element, then removes the top element. |
| `mod`   | `mod`         | Computes the remainder of dividing the second top element by the top element, then removes the top element. |
| `nop`   | `nop`         | Doesn't do anything. |
| `pchar` | `pchar`       | Prints the char whose ascii value is at the top of the stack. |
| `pstr`  | `pstr`        | Prints the string starting at the top of the stack. |
| `rotl`  | `rotl`        | Rotates the stack: the top element becomes the last one. |
| `rotr`  | `rotr`        | Rotates the stack: the last element becomes the top one. |
| `stack` | `stack`       | Sets the data format to a stack (LIFO). Default behavior. |
| `queue` | `queue`       | Sets the data format to a queue (FIFO). |

### push

* Usage: `push <int>`
* `<int>` should be an integer (handled via `atoi`, no overflow handling required).
* If `<int>` is not an integer, or no argument is given, prints `L<line_number>: usage: push integer` and exits with `EXIT_FAILURE`.
* In stack mode (the default), inserts at the top. In queue mode, inserts at the back.

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

### sub

* Usage: `sub`
* Subtracts the top element of the stack from the second top element. The result is stored in the second top element, and the top element is removed.
* If the stack contains less than two elements, prints `L<line_number>: can't sub, stack too short` and exits with `EXIT_FAILURE`.

### div

* Usage: `div`
* Divides the second top element of the stack by the top element. The result is stored in the second top element, and the top element is removed.
* If the stack contains less than two elements, prints `L<line_number>: can't div, stack too short` and exits with `EXIT_FAILURE`.
* If the top element of the stack is `0`, prints `L<line_number>: division by zero` and exits with `EXIT_FAILURE`.

### mul

* Usage: `mul`
* Multiplies the second top element of the stack with the top element. The result is stored in the second top element, and the top element is removed.
* If the stack contains less than two elements, prints `L<line_number>: can't mul, stack too short` and exits with `EXIT_FAILURE`.

### mod

* Usage: `mod`
* Computes the rest of the division of the second top element of the stack by the top element. The result is stored in the second top element, and the top element is removed.
* If the stack contains less than two elements, prints `L<line_number>: can't mod, stack too short` and exits with `EXIT_FAILURE`.
* If the top element of the stack is `0`, prints `L<line_number>: division by zero` and exits with `EXIT_FAILURE`.

### nop

* Usage: `nop`
* Doesn't do anything.

### pchar

* Usage: `pchar`
* Prints the char at the top of the stack, followed by a new line. The integer at the top of the stack is treated as the ascii value of the character to print.
* If the stack is empty, prints `L<line_number>: can't pchar, stack empty` and exits with `EXIT_FAILURE`.
* If the value is not in the ascii table (0-127), prints `L<line_number>: can't pchar, value out of range` and exits with `EXIT_FAILURE`.

### pstr

* Usage: `pstr`
* Prints the string starting at the top of the stack, followed by a new line. Each element, starting from the top, is treated as the ascii value of a character.
* Printing stops when the stack is exhausted, the value is `0`, or the value is not in the ascii table (0-127).
* If the stack is empty, prints only a new line. `pstr` never errors.

### rotl

* Usage: `rotl`
* Rotates the stack to the top: the top element becomes the last one, and the second top element becomes the first one.
* `rotl` never fails (an empty or single-element stack is left unchanged).

### rotr

* Usage: `rotr`
* Rotates the stack to the bottom: the last element becomes the top element.
* `rotr` never fails (an empty or single-element stack is left unchanged).

### stack

* Usage: `stack`
* Sets the format of the data to a stack (LIFO). This is the default behavior of the program.
* Switching mode does not move any existing data; it only changes how future `push` calls insert new elements.

### queue

* Usage: `queue`
* Sets the format of the data to a queue (FIFO).
* Switching mode does not move any existing data; it only changes how future `push` calls insert new elements.

## Comments

A line whose first non-space character is `#` is treated as a comment and ignored entirely, regardless of indentation or whether there's a space after the `#`.

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

```bash
$ cat bytecodes/28.m
push 72
pchar
$ ./monty bytecodes/28.m
H
```

```bash
$ cat bytecodes/31.m
push 1
push 2
push 3
push 4
push 0
push 110
push 0
push 108
push 111
push 111
push 104
push 99
push 83
pstr
$ ./monty bytecodes/31.m
School
```

```bash
$ cat bytecodes/47.m
queue
push 1
push 2
push 3
pall
stack
push 4
push 5
push 6
pall
add
pall
queue
push 11111
add
pall
$ ./monty bytecodes/47.m
1
2
3
6
5
4
1
2
3
11
4
1
2
3
15
1
2
3
11111
```

## Brainf\*ck

The `bf/` directory contains short Brainf\*ck scripts written and verified as part of this project:

| File | Description |
|------|--------------|
| `1000-school.bf` | Prints `School`, followed by a new line. |
| `1001-add.bf` | Reads two digits from stdin, adds them, and prints the (single-digit) result. |
| `1002-mul.bf` | Reads two digits from stdin, multiplies them, and prints the (single-digit) result. |
| `1003-mul.bf` | Reads two digits from stdin, multiplies them, and prints the result (which may be two digits), followed by a new line. |
| `bf_interpreter.c` | A small, self-contained Brainf\*ck interpreter in C, used to test the scripts above when a system `bf` package isn't available. Compile with `gcc -o bfrun bf_interpreter.c`, then run e.g. `./bfrun 1000-school.bf`. |

## File Organization

| File | Description |
|------|--------------|
| `monty.h` | Header file with `stack_t`, `instruction_t`, the global `head`/`queue_mode`, and function prototypes. |
| `main.c` | Entry point; opens the file, reads it line by line, drives execution. |
| `get_opcode.c` | Extracts the opcode and argument tokens from a line. |
| `execute_line.c` | Holds the global stack pointer and mode flag, and dispatches opcodes to their handler functions. |
| `free_stack.c` | Frees all nodes of the stack. |
| `push.c` | Implements the `push` opcode (and the `insert_node`/`is_valid_integer` helpers). |
| `pall.c` | Implements the `pall` opcode. |
| `pint.c` | Implements the `pint` opcode. |
| `pop.c` | Implements the `pop` opcode. |
| `swap.c` | Implements the `swap` opcode. |
| `add.c` | Implements the `add` opcode. |
| `sub.c` | Implements the `sub` opcode. |
| `div.c` | Implements the `div` opcode. |
| `mul.c` | Implements the `mul` opcode. |
| `mod.c` | Implements the `mod` opcode. |
| `nop.c` | Implements the `nop` opcode. |
| `pchar.c` | Implements the `pchar` opcode. |
| `pstr.c` | Implements the `pstr` opcode. |
| `rotl.c` | Implements the `rotl` opcode. |
| `rotr.c` | Implements the `rotr` opcode. |
| `stack_queue.c` | Implements the `stack` and `queue` opcodes. |
| `bytecodes/` | Sample `.m` byte code files for testing. |
| `bf/` | Brainf\*ck scripts and a small test interpreter (see above). |

## Author

