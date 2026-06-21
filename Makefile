CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89
SRC = main.c push.c pall.c pint.c pop.c swap.c add.c nop.c div.c mul.c sub.c pchar.c pstr.c rotl.c rotr.c stack_queue.c mod.c get_opcode.c free_stack.c execute_line.c
OBJ = $(SRC:.c=.o)
NAME = monty

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
