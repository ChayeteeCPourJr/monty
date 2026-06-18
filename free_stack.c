#include "monty.h"

/**
 * free_stack - frees all the nodes of the stack
 * @stack: pointer to the top (head) of the stack
 */
void free_stack(stack_t *stack)
{
	stack_t *tmp;

	while (stack != NULL)
	{
		tmp = stack->next;
		free(stack);
		stack = tmp;
	}
}
