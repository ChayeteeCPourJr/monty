#include "monty.h"

/**
 * pall - prints all the values on the stack, starting from the top
 * @stack: pointer to the top (head) of the stack
 * @line_number: the line number in the Monty bytecode file (unused)
 *
 * Description: usage: pall. If the stack is empty, prints nothing.
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

	(void)line_number;

	current = *stack;
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
