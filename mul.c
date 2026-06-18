#include "monty.h"

/**
 * mul - multiplies the second top element of the stack with the top
 * @stack: pointer to the top (head) of the stack
 * @line_number: the line number in the Monty bytecode file
 *
 * Description: usage: mul. If the stack contains less than two
 * elements, prints an error message to stderr and exits with
 * EXIT_FAILURE. The result is stored in the second top element,
 * and the top element is removed, leaving the stack one element
 * shorter with the result on top.
 */
void mul(stack_t **stack, unsigned int line_number)
{
	stack_t *top;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	top = *stack;
	top->next->n *= top->n;

	*stack = top->next;
	(*stack)->prev = NULL;

	free(top);
}
