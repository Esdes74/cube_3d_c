/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:43:44 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/07 19:42:32 by eslamber         ###   ########.fr       */
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
	int		col;
	int		lin;
	int		color;
	double	decimal;
	double	entier;
	t_image	*text;
	t_color	pix;
}	t_display;

// typedef struct s_collision
// {
// 	double	unknown;
// 	double	pos_x_dx;
// 	double	pos_y_dx;
// 	double	pos_x_dy;
// 	double	pos_y_dy;
// 	double	dist_tot_x;
// 	double	dist_tot_y;
// 	double	dif_x;
// 	double	dif_y;
// 	double	dist_x;
// 	double	dist_y;
// 	double	delta_x;
// 	double	delta_y;
// 	double	final_x;
// 	double	final_y;
// }	t_collision;

// typedef struct s_raytracing
// {
// 	int			i;
// 	double		begin_corner;
// 	double		mini_corner;
// 	double		maxi_corner;
// 	double		fov;
// 	double		dif;
// 	double		corner_col;
// 	double		dist;
// 	double		dist_max;
// 	t_collision	*col;
// }	t_raytracing;

// typedef struct s_display
// {
// 	int		c;
// 	int		f;
// 	double	wall;
// }	t_display;

// Raytracing functions
void	raycasting(t_cube *cube);

void	collision(t_raycasting *ray, t_cube *cube);

void	rotate_vector(t_vector *vec, double deg);

int		encodage_couleur(t_color col);

#endif