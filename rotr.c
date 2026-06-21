#include "monty.h"

/**
 * rotr - rotates the stack to the bottom
 * @stack: pointer to the top (head) of the stack
 * @line_number: the line number in the Monty bytecode file (unused)
 *
 * Description: usage: rotr. The last element of the stack becomes
 * the top element. rotr never fails (an empty or single-element
 * stack is left unchanged).
 */
void rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *last;

	(void)line_number;

	if (*stack == NULL || (*stack)->next == NULL)
		return;

	last = *stack;
	while (last->next != NULL)
		last = last->next;

	if (last->prev != NULL)
		last->prev->next = NULL;

	last->next = *stack;
	last->prev = NULL;
	(*stack)->prev = last;

	*stack = last;
}
