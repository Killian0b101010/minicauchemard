# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 14:05:47 by dnahon            #+#    #+#              #
#    Updated: 2025/08/07 17:59:59 by dnahon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	minishell
CC 			= 	cc
CFLAGS 		= 	-g3 -O0 -Wall -Wextra -Werror
DEBUGFLAGS	= 	-g3 -O0 -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -fsanitize=leak

LDFLAGS		= 	-lreadline -Llibft -lft
AR 			= 	ar rcs
RM 			= 	rm -f

SRC_DIR 	= 	./src
SRC 		= 	./src/core/main.c ./src/core/main_utils.c ./src/core/main_utils2.c\
				./src/execution/execution_utils.c ./src/execution/execution_processing.c ./src/execution/execution_pipes.c \
				./src/execution/builtins/echo.c ./src/execution/builtins/pwd.c ./src/execution/builtins/env.c \
				./src/execution/builtins/cd.c ./src/execution/builtins/export.c ./src/execution/builtins/unset.c \
				./src/execution/builtins/exec_builtins.c ./src/execution/builtins/exit.c \
				./src/execution/execute_commands.c ./src/execution/path.c \
				./src/parsing/tokenizer.c ./src/parsing/tokenizer_utils.c ./src/parsing/syntax_parsing.c \
				./src/expansion/expansion.c ./src/expansion/expansion_utils.c ./src/expansion/expansion_utils2.c ./src/expansion/expansion_helpers.c \
				./src/redirection/redirections.c ./src/redirection/redirection_utils.c \
				./src/utils/utils.c ./src/utils/utils2.c ./src/utils/utils3.c \
				./src/malloc/arena_collector.c ./src/malloc/split_arena.c ./src/malloc/utils_arena.c \
				./src/signal/handler.c ./src/signal/handler2.c \

LIBFT 		= 	./libft/libft.a
INCLUDES	= 	./includes/minishell.h ./libft/includes/libft.h

OBJ 		= 	$(SRC:.c=.o)
OBJ_B 		= 	$(SRC_B:.c=.o)

# Color codes
GREEN 		= 	\033[0;32m
YELLOW 		= 	\033[0;33m
RED 		= 	\033[0;31m
BLUE 		= 	\033[0;34m
PURPLE 		= 	\033[0;35m
CYAN 		= 	\033[0;36m
NC 			= 	\033[0m # No Color

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C libft --no-print-directory
	@echo "$(GREEN)Building $(NC)$(NAME)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c $(INCLUDES)
	@echo "$(CYAN)Compiling $(NC)$<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C libft clean --no-print-directory
	@echo "$(CYAN)Cleaning object files"
	@$(RM) $(OBJ) $(OBJ_B) libft.a

fclean: clean
	@$(MAKE) -C libft fclean --no-print-directory
	@echo "$(CYAN)Cleaning $(NC)$(NAME)"
	@$(RM) $(NAME)

re: fclean all

debug: $(OBJ)
	@$(MAKE) -C libft --no-print-directory
	@echo "$(YELLOW)Building $(NC)$(NAME) $(YELLOW)with debug flags"
	@$(CC) $(DEBUGFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

valgrind: $(NAME)
	@echo "$(YELLOW)🔍 Lancement de Valgrind sur ./minishell..."
	valgrind -q --suppressions=./ignore --trace-children=yes \
		--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes \
		./minishell

		


.PHONY: all clean fclean re debug valgrind
