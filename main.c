#include "monty.h"

/**
 * main - entry point for the Monty bytecode interpreter
 * @argc: argument count
 * @argv: argument vector; argv[1] should be the path to a .m file
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned int line_number = 0;
	char *opcode;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, file)) != -1)
	{
		line_number++;
		opcode = get_opcode(line);
		execute_line(opcode, line, line_number);
	}

	free(line);
	fclose(file);
	free_stack(head);

	return (EXIT_SUCCESS);
}
