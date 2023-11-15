# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 16:40:33 by eslamber          #+#    #+#              #
#    Updated: 2023/11/15 15:49:12 by eslamber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#
### Definitions of variables
#

# Compilation flags
FLAGS := -Wall -Werror -Wextra -g3
CC := gcc

FLAG_MLX := libft/minilibx/libmlx.a libft/minilibx/libmlx_Linux.a \
			libft/libft.a -lm -L/usr/lib -lXext -lX11 -lz

#
### Definition of names variables
#

# Definition of LIB variables
LIB_DIR := libft/
LIB := $(LIB_DIR)libft.a
MLX := $(LIB_DIR)minilibx/libmlx.a

# Definition of project variables
NAME := cube3D
HEADER := cube.h

# Definition of files variables
SRC := main.c \
	   parsing.c \
	   error.c
OBJ := $(SRC:%.c=.obj/%.o)

#
### Compilation rules
#


all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ $(FLAG_MLX) -L. $(LIB)

.obj/%.o: %.c $(HEADER) $(LIB) $(MLX)
	$(CC) $(FLAGS) -I/usr/include -Ilibft/mlx_linux -c $< -o $@

$(LIB): FORCE
	make -C $(LIB_DIR)

$(MLX): FORCE
	make -sC $(LIB_DIR)minilibx

#
### Cleanup rules
#

clean:
	@rm -rfv $(OBJ)
	make -sC libft clean

fclean:
	@rm -rfv $(OBJ)
	@rm -rfv $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re FORCE
