/*
 * A minimal, correct Brainf*ck interpreter.
 * Usage: ./bfrun script.bf
 * Reads program input from stdin (used by ',' instructions).
 */
#include <stdio.h>
#include <stdlib.h>

#define TAPE_SIZE 30000
#define CODE_MAX 1000000

int main(int argc, char *argv[])
{
	static char code[CODE_MAX];
	static unsigned char tape[TAPE_SIZE];
	static int match[CODE_MAX];
	int code_len = 0;
	int ptr = 0;
	int pc;
	FILE *f;
	int c;
	int stack[CODE_MAX];
	int sp = 0;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s script.bf\n", argv[0]);
		return (1);
	}

	f = fopen(argv[1], "r");
	if (f == NULL)
	{
		fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
		return (1);
	}

	while ((c = fgetc(f)) != EOF && code_len < CODE_MAX - 1)
		code[code_len++] = (char)c;
	fclose(f);

	/* Precompute matching brackets */
	for (pc = 0; pc < code_len; pc++)
	{
		if (code[pc] == '[')
			stack[sp++] = pc;
		else if (code[pc] == ']')
		{
			int open_pc = stack[--sp];

			match[open_pc] = pc;
			match[pc] = open_pc;
		}
	}

	pc = 0;
	while (pc < code_len)
	{
		switch (code[pc])
		{
		case '+':
			tape[ptr]++;
			break;
		case '-':
			tape[ptr]--;
			break;
		case '>':
			ptr++;
			break;
		case '<':
			ptr--;
			break;
		case '.':
			putchar(tape[ptr]);
			break;
		case ',':
			{
				int ch = getchar();

				tape[ptr] = (ch == EOF) ? 0 : (unsigned char)ch;
			}
			break;
		case '[':
			if (tape[ptr] == 0)
				pc = match[pc];
			break;
		case ']':
			if (tape[ptr] != 0)
				pc = match[pc];
			break;
		default:
			break;
		}
		pc++;
	}

	return (0);
}
