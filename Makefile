NAME := minishell

RL_DIR := /usr/local/opt/readline/
LIB_RL := -L$(RL_DIR)lib/

CC := gcc
CFLAGS := -Wall -Werror -Wextra -lreadline $(LIB_RL) -g

LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a
#LIBFT_FLAGS := -Llibft
LIB_I := -I$(LIBFT_DIR)

SRCS_DIR := ./srcs
SRCS := $(shell find $(SRCS_DIR) -name '*.c')
HEADER_I := -I$(SRCS_DIR) -I$(RL_DIR)include/

all: $(NAME)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $^ $(LIB_I) $(HEADER_I) -o $@ 
	#$(CC) $(CFLAGS) $^ $(LIB_INC) $(LIBFT_FLAGS) -o $@ 

$(LIBFT):
	@make -C ./libft

norminette:
	norminette -R CheckForbiddenSourceHeader *.h *.c

clean:
	@make fclean -C ./libft
	rm -rf *.dSYM *.o $(NAME)

fclean: clean

re: fclean all libft

.PHONY: clean fclean re norminette libft
