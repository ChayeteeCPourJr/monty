#include "monty.h"

/**
 * mod_op - computes the rest of the division of the second top
 * element of the stack by the top element
 * @stack: pointer to the top (head) of the stack
 * @line_number: the line number in the Monty bytecode file
 *
 * Description: usage: mod. If the stack contains less than two
 * elements, prints an error message to stderr and exits with
 * EXIT_FAILURE. If the top element of the stack is 0, prints a
 * division by zero error and exits with EXIT_FAILURE. Otherwise,
 * the result is stored in the second top element, and the top
 * element is removed, leaving the stack one element shorter with
 * the result on top.
 */
void mod_op(stack_t **stack, unsigned int line_number)
{
	stack_t *top;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	top = *stack;

	if (top->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	top->next->n %= top->n;

	*stack = top->next;
	(*stack)->prev = NULL;

	free(top);
}
