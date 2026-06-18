#include "monty.h"

/**
 * get_opcode - extracts the opcode (first word) from a line of
 * Monty bytecode
 * @line: the line read from the file
 *
 * Return: pointer to the opcode string (statically/strtok managed),
 * or NULL if the line is empty / contains only whitespace
 */
char *get_opcode(char *line)
{
	char *opcode;

	if (line == NULL)
		return (NULL);

	opcode = strtok(line, " \t\r\n");

	return (opcode);
}

/**
 * get_argument - extracts the next token (argument) from the line
 * previously tokenized by get_opcode via strtok
 * @line: pass NULL to continue tokenizing the previously-set line
 *
 * Return: pointer to the argument string, or NULL if none remains
 */
char *get_argument(char *line)
{
	char *argument;

	argument = strtok(line, " \t\r\n");

	return (argument);
}
