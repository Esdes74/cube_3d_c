/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:35:29 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/06 10:55:52 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
# include "libft/minilibx/mlx.h"

# define WIN_W 1900
# define WIN_H 1080//768
# define NAME "CUBE 3D"

# define WALL 650 // taille d'un mur a une distance de 1 yard (en pixel)
# define YARD 20 // valeur de 1 yard

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

enum e_or
{
	NORD,
	SUD,
	EST,
	OUEST,
	NONE,
};

typedef struct s_perso
{
	size_t		x;
	size_t		y;
	enum e_or	orient;
}	t_perso;

typedef struct s_cube
{
	int		perso;
	size_t	size_map;
	t_perso	personnage;
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

typedef struct s_point
{
	size_t	x;
	size_t	y;
}	t_point;

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
	UNVALID_SPACE,
	MISSED_DIFFUSION,
}	t_error;

typedef enum e_mod
{
	END,
	CONT,
}	t_mod;

// Parsing
void	parsing(const char *av, t_cube *cube);

void	check_file(const int fd, t_cube *cube);

void	check_map(const int fd, t_cube *cube);

void	verif_map(t_cube *cube);

void	diffusion(const size_t x, const size_t y, char **dup);

void	ascending_diffusion(long long int i, long long int *j, \
const t_point *p, char **dup);

void	descending_diffusion(long long int i, long long int *j, \
const size_t y, char **dup);

void	fill_dup(const long long int i, const long long int j, char **dup);

// Error gestion
void	error(const t_error err, const t_mod mod);

// Free functions
void	free_all(t_cube *cube);

// Utils function
char	*pass_newline(const int fd, char *line);

#endif
