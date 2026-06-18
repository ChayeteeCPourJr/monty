#include "monty.h"

/**
 * is_valid_integer - checks whether a string represents a valid
 * (optionally signed) integer
 * @arg: the string to check
 *
 * Return: 1 if arg is a valid integer, 0 otherwise
 */
int is_valid_integer(char *arg)
{
	int i = 0;

	if (arg == NULL || *arg == '\0')
		return (0);

	if (arg[i] == '-' || arg[i] == '+')
		i++;

	if (arg[i] == '\0')
		return (0);

	for (; arg[i] != '\0'; i++)
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
	}

	return (1);
}

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
	stack_t *new_node;

	arg = get_argument(NULL);

	if (!is_valid_integer(arg))
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
