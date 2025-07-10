# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 14:05:47 by dnahon            #+#    #+#              #
#    Updated: 2025/07/10 15:46:26 by kiteixei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	minishell
CC 			= 	cc
CFLAGS 		= 	-g3 -O0 -Wall -Wextra -Werror

LDFLAGS		= 	-lreadline -Llibft -lft
AR 			= 	ar rcs
RM 			= 	rm -f

SRC_DIR 	= 	./src
SRC 		= 	./src/builtins/echo.c ./src/tokens/tokenizer_utils.c ./src/tokens/tokenizer.c \
				./src/utils.c ./src/main.c ./src/builtins/cd.c

LIBFT 		= 	./libft/libft.a
INCLUDES	= 	./includes/pipex.h ./includes/minishell.h ./libft/includes/libft.h

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

.PHONY: all clean fclean re bonus
