#include "monty.h"

/**
 * pstr - prints the string starting at the top of the stack,
 * followed by a new line
 * @stack: pointer to the top (head) of the stack
 * @line_number: the line number in the Monty bytecode file (unused)
 *
 * Description: usage: pstr. Each element of the stack, starting
 * from the top, is treated as the ascii value of a character to
 * print. Printing stops when the stack is exhausted, the value is
 * 0, or the value is not within the ascii table range (0-127). If
 * the stack is empty, only a new line is printed.
 */
void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

	(void)line_number;

	current = *stack;

	while (current != NULL && current->n != 0 &&
	       current->n >= 0 && current->n <= 127)
	{
		printf("%c", current->n);
		current = current->next;
	}

	printf("\n");
}
