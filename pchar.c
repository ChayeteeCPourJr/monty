#include "monty.h"

/**
 * pchar - prints the char at the top of the stack, followed by a
 * new line
 * @stack: pointer to the top (head) of the stack
 * @line_number: the line number in the Monty bytecode file
 *
 * Description: usage: pchar. The integer at the top of the stack is
 * treated as the ascii value of the character to print. If the
 * stack is empty, prints an error message and exits with
 * EXIT_FAILURE. If the value is not within the ascii table range
 * (0-127), prints an error message and exits with EXIT_FAILURE.
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n < 0 || (*stack)->n > 127)
	{
		fprintf(stderr, "L%u: can't pchar, value out of range\n",
			line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	printf("%c\n", (*stack)->n);
}
