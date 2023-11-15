/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:35:29 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/15 19:24:03 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <fcntl.h>
# include "libft/libft.h"
# include "libft/minilibx/mlx.h"

# define WIN_W 1200//1366
# define WIN_H 650//768
# define NAME "CUBE 3D"

typedef struct	s_color
{
	int first;
	int second;
	int third;
}	t_color;

typedef struct	s_image
{
	int		width;
	int		height;
	int		*bits;
	int		*size;
	int		*endian;
	void	*ptr_image;
}	t_image;

typedef struct	s_cube 
{
	t_color f;
	t_color c;
	t_image	no;
	t_image	so;
	t_image	we;
	t_image	ea;
	void	*mlx;
	void	*win;
	char    **map;
}	t_cube;

typedef enum	e_error
{
	NBR_ARG,
	EXTENSION,
	OPEN,
	MLX,
	WIN,
	EMPTY_FILE,
	UNCOMPLETE_FILE,
	MALLOC,
	TEXTURE_FORMAT,
}	t_error;

// Parsing
void	parsing(char *av, t_cube *cube);

// Error gestion
void	error(t_error err);

// Free functions
void	free_all(t_cube *cube);

#endif
