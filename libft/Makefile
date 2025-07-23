# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 17:04:07 by dnahon            #+#    #+#              #
#    Updated: 2025/07/14 18:29:42 by dnahon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
SRC_DIR = ./src/libft
SRC = ./src/libft/get_next_line/get_next_line.c \
	./src/libft/get_next_line/get_next_line_utils.c \
	./src/libft/alloc/ft_calloc.c ./src/libft/alloc/ft_free.c \
	./src/libft/alloc/ft_malloc.c ./src/libft/alloc/ft_realloc.c \
	./src/libft/array/ft_intcpy.c ./src/libft/array/ft_intdup.c \
	./src/libft/array/ft_intsort.c ./src/libft/checks/ft_isalnum.c \
	./src/libft/checks/ft_isalpha.c ./src/libft/checks/ft_isascii.c \
	./src/libft/checks/ft_isblank.c ./src/libft/checks/ft_iscntrl.c \
	./src/libft/checks/ft_isdigit.c ./src/libft/checks/ft_isgraph.c \
	./src/libft/checks/ft_islower.c ./src/libft/checks/ft_isprint.c \
	./src/libft/checks/ft_ispunct.c ./src/libft/checks/ft_isspace.c \
	./src/libft/checks/ft_isupper.c ./src/libft/checks/ft_isxdigit.c \
	./src/libft/convert/ft_atoi_strict.c ./src/libft/convert/ft_atoi.c \
	./src/libft/convert/ft_atol_strict.c ./src/libft/convert/ft_atol.c \
	./src/libft/convert/ft_atoll_strict.c ./src/libft/convert/ft_atoll.c \
	./src/libft/convert/ft_tolower.c ./src/libft/convert/ft_toupper.c \
	./src/libft/io/ft_putchar_fd.c ./src/libft/io/ft_putchar.c \
	./src/libft/io/ft_putend_fd.c ./src/libft/io/ft_putnbr_fd.c \
	./src/libft/io/ft_putnbr.c ./src/libft/io/ft_putstr_fd.c \
	./src/libft/io/ft_putstr.c ./src/libft/math/ft_abs.c \
	./src/libft/math/ft_intlen.c ./src/libft/math/ft_max.c \
	./src/libft/math/ft_min.c ./src/libft/math/ft_nmax.c \
	./src/libft/math/ft_nmin.c ./src/libft/mem/ft_bzero.c \
	./src/libft/mem/ft_memccpy.c ./src/libft/mem/ft_memchr.c \
	./src/libft/mem/ft_memcmp.c ./src/libft/mem/ft_memcpy.c \
	./src/libft/mem/ft_memmove.c ./src/libft/mem/ft_memset.c \
	./src/libft/str/compare/ft_is_palindrome.c ./src/libft/str/compare/ft_strcmp.c \
	./src/libft/str/compare/ft_strncmp.c ./src/libft/str/concat/ft_strcat.c \
	./src/libft/str/concat/ft_strlcat.c ./src/libft/str/concat/ft_strncat.c \
	./src/libft/str/copy/ft_strcpy.c ./src/libft/str/copy/ft_strncpy.c ./src/libft/str/copy/ft_strdup.c \
	./src/libft/str/copy/ft_strlcpy.c ./src/libft/str/info/ft_strlen.c \
	./src/libft/str/info/ft_strnlen.c ./src/libft/str/modify/ft_strrev.c \
	./src/libft/str/modify/ft_strjoin.c ./src/libft/str/modify/ft_substr.c \
	./src/libft/str/modify/ft_strtrim.c ./src/libft/str/search/ft_strchr.c \
	./src/libft/str/search/ft_strchrnul.c ./src/libft/str/search/ft_strnstr.c \
	./src/libft/str/search/ft_strrchr.c ./src/libft/str/search/ft_strstr.c \
	./src/libft/convert/ft_itoa.c ./src/libft/str/modify/ft_split.c \
	./src/libft/str/modify/ft_strmapi.c ./src/libft/str/modify/ft_striteri.c \
	./src/libft/linked_list/ft_lstnew.c ./src/libft/linked_list/ft_lstadd_front.c \
	./src/libft/linked_list/ft_lstsize.c ./src/libft/linked_list/ft_lstlast.c \
	./src/libft/linked_list/ft_lstadd_back.c ./src/libft/linked_list/ft_lstdelone.c \
	./src/libft/linked_list/ft_lstclear.c ./src/libft/linked_list/ft_lstiter.c \
	./src/libft/linked_list/ft_lstmap.c ./src/libft/printf/ft_printf_utils.c \
	./src/libft/printf/ft_printf.c ./src/libft/printf/ft_printnbr.c \
	./src/libft/printf/ft_printnbrui.c ./src/libft/printf/ft_printptr.c \
	./src/libft/printf/ft_putnbr_base.c ./src/libft/alloc/ft_free_split.c \

INCLUDES = ./includes/libft.h ./includes/ft_printf.h ./includes/get_next_line.h

OBJ = $(SRC:.c=.o)

# Color codes
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
NC = \033[0m # No Color

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Building $(NC)$(NAME)"
	@$(AR) $(NAME) $(OBJ)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@echo "$(CYAN)Compiling $(NC)$<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(CYAN)Cleaning object files"
	@$(RM) $(OBJ)
fclean: clean
	@echo "$(CYAN)Cleaning $(NC)$(NAME)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re