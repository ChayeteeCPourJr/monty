#include "monty.h"

/**
 * stack_mode - sets the format of the data to a stack (LIFO)
 * @stack: pointer to the top (head) of the stack (unused)
 * @line_number: the line number in the Monty bytecode file (unused)
 *
 * Description: usage: stack. This is the default behavior of the
 * program. Switching mode does not move any data; it only changes
 * how push() inserts new elements.
 */
void stack_mode(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;

	queue_mode = 0;
}

/**
 * queue_mode_op - sets the format of the data to a queue (FIFO)
 * @stack: pointer to the top (head) of the stack (unused)
 * @line_number: the line number in the Monty bytecode file (unused)
 *
 * Description: usage: queue. Switching mode does not move any
 * data; it only changes how push() inserts new elements.
 */
void queue_mode_op(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;

	queue_mode = 1;
}
