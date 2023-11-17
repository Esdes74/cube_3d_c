/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:35:29 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/17 22:20:57 by eslamber         ###   ########.fr       */
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

# define PERSO "NSEW"
# define COMP " 10\n\0"

typedef struct s_color
{
	int	red;
	int	gre;
	int	blu;
}	t_color;

typedef struct s_image
{
	int		width;
	int		height;
	int		bits;
	int		size;
	int		endian;
	char	*img;
	void	*ptr_image;
}	t_image;

typedef struct s_cube
{
	int		perso;
	size_t	size_map;
	t_color	f;
	t_color	c;
	t_image	no;
	t_image	so;
	t_image	we;
	t_image	ea;
	void	*mlx;
	void	*win;
	char	**map;
}	t_cube;

typedef enum e_error
{
	NBR_ARG,
	EXTENSION,
	OPEN,
	MLX,
	WIN,
	EMPTY_FILE,
	EMPTY_MAP,
	UNCOMPLETE_FILE,
	MALLOC,
	TEXTURE_FORMAT,
	XPM_FILE,
	IMG_ADDR,
	WRONG_IDENTIFIER,
	W_RGB,
	WRONG_COMPONENT,
	DOUBLE_PERSO,
	OPENED_MAP,
	SAME_TEXTURE,
	DB_TEXTURE_IDENTIFIER,
	NO_PERSO,
}	t_error;

typedef enum e_mod
{
	END,
	CONT,
}	t_mod;

// Parsing
void	parsing(char *av, t_cube *cube);

void	check_file(int fd, t_cube *cube);

void	check_map(int fd, t_cube *cube);

void	verif_map(t_cube *cube);

// Error gestion
void	error(t_error err, t_mod mod);

// Free functions
void	free_all(t_cube *cube);

// Utils function
char	*pass_newline(int fd, char *line);

#endif
