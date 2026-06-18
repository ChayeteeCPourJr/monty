#include "monty.h"

/**
 * push - pushes an element onto the stack
 * @stack: pointer to the top (head) of the stack
 * @line_number: the line number in the Monty bytecode file
 *
 * Description: usage: push <int>. If <int> is not an integer, or
 * if no argument is given, prints an error message to stderr and
 * exits with EXIT_FAILURE.
 */
void push(stack_t **stack, unsigned int line_number)
{
	char *arg;
	int i, is_digit_flag;
	stack_t *new_node;

	arg = get_argument(NULL);

	is_digit_flag = (arg != NULL && *arg != '\0');
	if (is_digit_flag)
	{
		i = 0;
		if (arg[i] == '-' || arg[i] == '+')
			i++;
		if (arg[i] == '\0')
			is_digit_flag = 0;
		for (; arg[i] != '\0' && is_digit_flag; i++)
		{
			if (arg[i] < '0' || arg[i] > '9')
				is_digit_flag = 0;
		}
	}

	if (!is_digit_flag)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	new_node->n = atoi(arg);
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = new_node;

	*stack = new_node;
}
