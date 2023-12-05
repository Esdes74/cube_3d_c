# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 16:40:33 by eslamber          #+#    #+#              #
#    Updated: 2023/12/05 16:47:00 by eslamber         ###   ########.fr        #
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
HEADER := cube.h \
		  display.h

# Definition of files variables
SRC := main.c \
	   parsing.c \
	   check_file.c \
	   error.c \
	   free_all.c \
	   check_map.c \
	   verif_map.c \
	   diffusion.c \
	   ascending_diffusion.c \
	   descending_diffusion.c \
	   fill_dup.c \
	   raytracing.c \
	   utils.c
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

# Debug
debug:
	make -C libft debug
	make -C ./ "FLAGS = -Wall -Wextra -fsanitize=address \
	-fno-omit-frame-pointer -g3"

val_deb:
	make -C libft valgrind_deb
	make -C ./ "FLAGS = -Wall -Werror -Wextra -g3"

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

re_deb: fclean debug

re_val: fclean val_deb

.PHONY: all clean fclean re FORCE
