# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 21:18:48 by dgomez-m          #+#    #+#              #
#    Updated: 2024/01/01 22:08:54 by dgomez-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT = lib/libft
GNL = lib/get_next_line

SRCS = basicos.c basicos2.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
    $(MAKE) -C $(LIBFT)
    $(MAKE) -C $(GNL)
    $(CC) $(CFLAGS) -I $(LIBFT) -I $(GNL) -L $(LIBFT) -lft -L $(GNL) -lgnl $(OBJS) -o $(NAME)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    $(MAKE) -C $(LIBFT) clean
    $(MAKE) -C $(GNL) clean
    rm -f $(OBJS)

fclean: clean
    $(MAKE) -C $(LIBFT) fclean
    $(MAKE) -C $(GNL) fclean
    rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re