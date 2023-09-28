# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmuller <jmuller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/06 12:20:32 by jmuller           #+#    #+#              #
#    Updated: 2023/08/28 16:18:41 by jmuller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME	:= fdf
CFLAGS	:= -g -Wextra -Wall -Werror -Wunreachable-code -O0
LIBMLX	:= ./MLX42
LIBMLX42 := $(LIBMLX)/build/libmlx42.a

HEADERS	:= -I ./include -I $(LIBMLX)/include -I /nfs/homes/jmuller/Aufgaben/libft -I /nfs/homes/jmuller/Aufgaben/get_next_line
LIBS	:= $(LIBMLX)/build/libmlx42.a /nfs/homes/jmuller/Aufgaben/libft/libft.a /nfs/homes/jmuller/Aufgaben/get_next_line/gnl.a /nfs/homes/jmuller/Aufgaben/printf/libftprintf.a -ldl -lglfw -pthread -lm
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

# The all rule is the first rule and it depends on libmlx and $(NAME). When you run make without arguments, it will execute this rule and build libmlx and $(NAME) in that order.

all: $(NAME)

# The libmlx rule uses cmake to generate a build system for the MLX42 library and then builds the library with make.

$(LIBMLX42):
	@cmake $(LIBMLX) -DDEBUG=ON -B $(LIBMLX)/build && $(MAKE) -C $(LIBMLX)/build -j4

#The %.o: %.c rule is a pattern rule. It will be used for each .c file in SRCS to create a corresponding .o file in OBJS

# @$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"
%.o: %.c
	@$(CC) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(LIBMLX42) $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re
