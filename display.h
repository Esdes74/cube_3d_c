/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:43:44 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/05 18:35:03 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

typedef struct s_collision
{
	double	unknown;
	double	pos_x_dx;
	double	pos_y_dx;
	double	pos_x_dy;
	double	pos_y_dy;
	double	dist_tot_x;
	double	dist_tot_y;
	double	dif_x;
	double	dif_y;
	double	dist_x;
	double	dist_y;
	double	delta_x;
	double	delta_y;
	double	final_x;
	double	final_y;
}	t_collision;

typedef struct s_raytracing
{
	int			i;
	double		begin_corner;
	double		mini_corner;
	double		maxi_corner;
	double		fov;
	double		dif;
	double		corner_col;
	double		dist;
	double		dist_max;
	t_collision	*col;
}	t_raytracing;

typedef struct s_display
{
	int		c;
	int		f;
	double	wall;
}	t_display;

// Raytracing functions
void	raytracing(t_cube *cube);

#endif