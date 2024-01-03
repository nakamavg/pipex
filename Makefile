# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 21:18:48 by dgomez-m          #+#    #+#              #
#    Updated: 2024/01/03 01:24:52 by dgomez-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
CFLAGS			+=	-g -Iinclude -Isrc -Ofast
RM				=	rm -rf
PIPEX			=	$(NAME)
NAME			=	pipex

# Libft

LIBFT_DIR		=	/lib/libft
LIBFT_FILE		=	$(LIBFT_DIR)/$(LIBFT)
CFLAGS			+=	-I $(LIBFT_DIR)/include

# Sources and objects

SRC_DIR			=	src

