# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 21:18:48 by dgomez-m          #+#    #+#              #
#    Updated: 2024/01/03 05:44:10 by dgomez-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ... and then the rules to compile the program
# Compiler and flags
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
includes		=	./includes
CFLAGS			+=	-I. -I./includes
RM				=	rm -rf
NAME			=	pipex

# Libft
LIBFT_DIR		=	lib/libft
LIBFT			=	$(LIBFT_DIR)/libft.a
CFLAGS			+=	-I $(LIBFT_DIR)

# Sources and objects
SRC				=	main.c process.c free.c  error.c
OBJ				=	$(SRC:.c=.o)


all: $(NAME)
	
$(NAME): $(LIBFT) $(OBJ)
	$(CC)	$(CFLAGS)	-o	$(NAME)	$(OBJ)	-L$(LIBFT_DIR)	-lft

$(LIBFT):
	 make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: all clean fclean re

.PHONY: all clean fclean re


# ... and then the rules to compile the program