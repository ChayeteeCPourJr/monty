#include "monty.h"

stack_t *head = NULL;
int queue_mode = 0;

/**
 * execute_line - looks up the opcode in the instruction table and
 * calls the matching function, or exits with an error if unknown
 * @opcode: the opcode string (already extracted from the line)
 * @line: unused here, kept for interface symmetry / future opcodes
 * @line_number: the current line number in the bytecode file
 */
void execute_line(char *opcode, char *line, unsigned int line_number)
{
	instruction_t instructions[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{"div", div_op},
		{"mul", mul},
		{"sub", sub},
		{"pchar", pchar},
		{"pstr", pstr},
		{"rotl", rotl},
		{"rotr", rotr},
		{"stack", stack_mode},
		{"queue", queue_mode_op},
		{NULL, NULL}
	};
	int i;

	(void)line;

	if (opcode == NULL || opcode[0] == '#')
		return;

	for (i = 0; instructions[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, instructions[i].opcode) == 0)
		{
			instructions[i].f(&head, line_number);
			return;
		}
	}

	fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
	free_stack(head);
	exit(EXIT_FAILURE);
}
