/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cube.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:04:45 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/11 18:13:03 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_CUBE_H
# define STRUCT_CUBE_H

# include "libft/libft.h"

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
	int		**pix_img;
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

#endif