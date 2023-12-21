/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:43:44 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/21 18:56:36 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include <math.h>
# include "struct_cube.h"
# include "libft/libft.h"

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_int_vector
{
	int	x;
	int	y;
}	t_int_vector;

typedef struct s_raycasting
{
	int				c;
	int				f;
	int				type;
	int				wall;
	size_t			i;
	double			cam_mul;
	double			perp;
	t_vector		pos;
	t_vector		dir;
	t_vector		pla;
	t_vector		ray_dir;
	t_vector		delta;
	t_vector		sdist;
	t_int_vector	cur;
	t_int_vector	step;
}	t_raycasting;

typedef struct s_display
{
	int		wall;
	int		start;
	int		end;
	int		lin;
	int		text_x;
	double	step;
	double	text_pos;
	t_image	*text;
}	t_display;

// Raytracing functions
void	raycasting(t_raycasting *ray, t_cube *cube);

void	collision(t_raycasting *ray, t_cube *cube);

void	rotate_vector(t_vector *vec, double deg);

void	display_texture(int *h, t_display *dis, t_raycasting *ray, \
t_cube *cube);

void	fill_vector(t_vector *v, double fst, double sec);

#endif