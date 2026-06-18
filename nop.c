#include "monty.h"

/**
 * nop - doesn't do anything
 * @stack: pointer to the top (head) of the stack (unused)
 * @line_number: the line number in the Monty bytecode file (unused)
 *
 * Description: usage: nop. Has no effect on the stack.
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
