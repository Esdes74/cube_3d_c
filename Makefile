# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 16:40:33 by eslamber          #+#    #+#              #
#    Updated: 2023/12/22 12:55:46 by eslamber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#
### Definitions of variables
#

# Compilation flags
FLAGS := -Wall -Werror -Wextra
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
HEADER := struct_cube.h

# Definition of files variables
SRC := ascending_diffusion.c \
	   check_file.c \
	   check_map.c \
	   collision.c \
	   descending_diffusion.c \
	   diffusion.c \
	   display_texture.c \
	   encodage_texture.c \
	   error.c \
	   fill_dup.c \
	   fill_vector.c \
	   free_all.c \
	   key_events.c \
	   loop.c \
	   main.c \
	   parsing.c \
	   put_pix.c \
	   raycasting.c \
	   rotate_vector.c \
	   utils.c \
	   verif_map.c
OBJ := $(SRC:%.c=.obj/%.o)

SRC_CUBE_H := ascending_diffusion.c \
			  check_file.c \
			  check_map.c \
			  descending_diffusion.c \
			  diffusion.c \
			  encodage_texture.c \
			  error.c \
			  fill_dup.c \
			  free_all.c \
			  parsing.c \
			  put_pix.c \
			  utils.c \
			  verif_map.c
OBJ_CUBE_H := $(SRC_CUBE_H:%.c=.obj/%.o)

SRC_DISPLAY_H := fill_vector.c \
				 raycasting.c \
				 rotate_vector.c
OBJ_DISPLAY_H := $(SRC_DISPLAY_H:%.c=.obj/%.o)

SRC_KEY_EVENTS_H := loop.c
OBJ_KEY_EVENTS_H := $(SRC_KEY_EVENTS_H:%.c=.obj/%.o)

SRC_CUBE_DISPLAY := collision.c \
					display_texture.c
OBJ_CUBE_DISPLAY := $(SRC_CUBE_DISPLAY:%.c=.obj/%.o)

SRC_CUBE_KEY := key_events.c
OBJ_CUBE_KEY := $(SRC_CUBE_KEY:%.c=.obj/%.o)

SRC_CUBE_DIS_KEY := main.c
OBJ_CUBE_DIS_KEY := $(SRC_CUBE_DIS_KEY:%.c=.obj/%.o)

#
### Compilation rules
#

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ $(FLAG_MLX) -L. $(LIB)

$(OBJ_CUBE_H): .obj/%.o: %.c cube.h struct_cube.h $(LIB) $(MLX)
	$(CC) $(FLAGS) -I/usr/include -Ilibft/mlx_linux -c $< -o $@

$(OBJ_DISPLAY_H): .obj/%.o: %.c display.h struct_cube.h $(LIB) $(MLX)
	$(CC) $(FLAGS) -I/usr/include -Ilibft/mlx_linux -c $< -o $@

$(OBJ_KEY_EVENTS_H): .obj/%.o: %.c key_events.h struct_cube.h $(LIB) $(MLX)
	$(CC) $(FLAGS) -I/usr/include -Ilibft/mlx_linux -c $< -o $@

$(OBJ_CUBE_DISPLAY): .obj/%.o: %.c cube.h display.h struct_cube.h $(LIB) $(MLX)
	$(CC) $(FLAGS) -I/usr/include -Ilibft/mlx_linux -c $< -o $@

$(OBJ_CUBE_KEY): .obj/%.o: %.c cube.h key_events.h struct_cube.h $(LIB) $(MLX)
	$(CC) $(FLAGS) -I/usr/include -Ilibft/mlx_linux -c $< -o $@

$(OBJ_CUBE_DIS_KEY): .obj/%.o: %.c cube.h key_events.h display.h \
struct_cube.h $(LIB) $(MLX)
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
