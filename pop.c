#include "monty.h"

/**
 * pop - removes the top element of the stack
 * @stack: pointer to the top (head) of the stack
 * @line_number: the line number in the Monty bytecode file
 *
 * Description: usage: pop. If the stack is empty, prints an error
 * message to stderr and exits with EXIT_FAILURE.
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	tmp = *stack;
	*stack = (*stack)->next;

	if (*stack != NULL)
		(*stack)->prev = NULL;

	free(tmp);
}

