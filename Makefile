NAME := pipex
LIBFT_DIR = libft/
LIBFT_EXEC = libft/libft.a
SRCFILES := pipex.c \
			pipex_err.c
CC = gcc
CFLAGS = -Wextra -Werror -Wall
OBJS := $(SRCFILES:.c=.o) 

all: $(NAME)

exec:
	$(CC) -g $(CFLAGS) $(SRCFILES)
$(NAME): $(OBJS)
	make -C libft/
clean:
	# rm -f *.o
	rm -f $(OBJS)
	make clean -C libft/
fclean:	clean
	rm -f $(NAME)
	make fclean -C libft/
	
re:		fclean all

.PHONY: clean fclean re