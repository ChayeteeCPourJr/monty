#include "monty.h"

/**
 * rotl - rotates the stack to the top
 * @stack: pointer to the top (head) of the stack
 * @line_number: the line number in the Monty bytecode file (unused)
 *
 * Description: usage: rotl. The top element of the stack becomes
 * the last one, and the second top element becomes the first one.
 * rotl never fails (an empty or single-element stack is left
 * unchanged).
 */
void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *top, *last;

	(void)line_number;

	if (*stack == NULL || (*stack)->next == NULL)
		return;

	top = *stack;
	*stack = top->next;
	(*stack)->prev = NULL;

	last = *stack;
	while (last->next != NULL)
		last = last->next;

	last->next = top;
	top->prev = last;
	top->next = NULL;
}
