/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:17:11 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/27 20:05:12 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

static double	collision_nord(double test, double x, double y, char **map);

void	raytracing(t_cube *cube)
{
	double	angle_principale;

	if (cube->personnage.orient == NORD)
		angle_principale = - (M_PI / 2.0);
	else if (cube->personnage.orient == SUD)
		angle_principale = M_PI / 2.0;
	else if (cube->personnage.orient == EST)
		angle_principale = 0;
	else if (cube->personnage.orient == OUEST)
		angle_principale = M_PI;

	double	fov;
	double	angle_mini;
	double	angle_maxi;
	double	dif;
	int		i;
	double	test;
	double	dist;

	fov = M_PI / 4;
	angle_mini = angle_principale - fov;
	angle_maxi = angle_principale + fov;

	dif = angle_maxi - angle_mini;
	dif = dif / WIN_W;
	test = angle_mini;
	i = 0;
	mlx_string_put(cube->mlx, cube->win, cube->personnage.y * 100, cube->personnage.x * 100, 1000000222, "X");
	while (test < angle_maxi)
	{
		dist = collision_nord(test, cube->personnage.x + 0.5, cube->personnage.y + 0.5, cube->map);
		mlx_pixel_put(cube->mlx, cube->win, (int) ((double) cube->personnage.y * 100.0) + (cos(test) * dist * 50.0), (int) ((double) cube->personnage.x * 100.0) + (sin(test) * dist * 50.0), 1000000222);
		test += dif;
		i++;
	}
	ft_printf_fd(2, "i = %d\n", i);
	mlx_loop(cube->mlx);
}

static double	collision_nord(double test, double x, double y, char **map)
{
	double	unknown;
	double	pos_x_dx = x;
	double	pos_y_dx = y;
	double	pos_x_dy = x;
	double	pos_y_dy = y;
	double	dist_tot_x = 0;
	double	dist_tot_y = 0;
	double	dif_x = 0.5;
	double	dif_y = 0.5;
	double	dist_x = 0;
	double	dist_y = 0;
	// double	dif_delta_x = 0;
	// double	dif_delta_y = 0;
	double	delta_x = 0;
	double	delta_y = 0;

	unknown = (dif_x) / tan(test);
	dist_x = sqrt(dif_x * dif_x + unknown * unknown);
	unknown = dif_y * tan(test);
	dist_y = sqrt(dif_x * dif_x + unknown * unknown);
	unknown = 1 / tan(test);
	delta_x = sqrt(unknown * unknown + 1);
	unknown = tan(test);
	delta_y = sqrt(unknown * unknown + 1);
	while (1)
	{
		if (dist_tot_x == 0 && ((dist_tot_y == 0 && \
		dist_tot_x + dist_x <= dist_tot_y + dist_y) || \
		(dist_tot_y != 0 && \
		dist_tot_x + dist_x <= dist_tot_y + delta_y))) // Travail sur x
		{
			pos_x_dx = x - dif_x;
			if (test < - (M_PI / 2))
				pos_y_dx = y - ((dif_x) / tan(test));
			else
				pos_y_dx = y + ((dif_x) / tan(test));
			if (map[((int) pos_x_dx) - 1][(int) pos_y_dx] == '1')
				return (dist_x);
			dist_tot_x = dist_x;
		}
		else if (dist_tot_y == 0 && ((dist_tot_x == 0 && \
		dist_tot_x + dist_x > dist_tot_y + dist_y) || \
		(dist_tot_x != 0 && \
		dist_tot_x + delta_x > dist_tot_y + dist_y))) // Travail sur y
		{
			if (test < - (M_PI / 2))
			{
				pos_x_dy = x - (dif_y * tan(test));
				pos_y_dy = y - dif_y;
			}
			else
			{
				pos_x_dy = x + (dif_y * tan(test));
				pos_y_dy = y + dif_y;
			}
			if (test > M_PI / 2)
			{
				if (map[(int) pos_x_dy][((int) pos_y_dy)] == '1')
					return (dist_y);
			}
			else
				if (map[(int) pos_x_dy][(int) pos_y_dy - 1] == '1')
					return (dist_y);
			dist_tot_y = dist_y;
		}
		else if (dist_tot_x != 0 && ((dist_tot_y == 0 && \
		dist_tot_x + delta_x <= dist_tot_y + dist_y) || \
		(dist_tot_y != 0 && \
		dist_tot_x + delta_x <= dist_tot_y + delta_y)))
		{
			pos_x_dx -= 1;
			pos_y_dx -= 1 / tan(test);
			if (map[(int) pos_x_dx - 1][(int) pos_y_dx] == '1')
				return (dist_tot_x + delta_x);
			dist_tot_x += delta_x;
		}
		else if (dist_tot_y != 0 && ((dist_tot_x == 0 && \
		dist_tot_x + dist_x > dist_tot_y + delta_y) || \
		(dist_tot_x != 0 && \
		dist_tot_x + delta_x > dist_tot_y + delta_y)))
		{
			if (test < - (M_PI / 2))
			{
				pos_x_dy -= (dif_y * tan(test));
				pos_y_dy -= dif_y;
			}
			else
			{
				pos_x_dy += (dif_y * tan(test));
				pos_y_dy += dif_y;
			}
			if (test > M_PI / 2)
			{
				if (map[(int) pos_x_dy][((int) pos_y_dy)] == '1')
					return (dist_tot_y + delta_y);
			}
			else
				if (map[(int) pos_x_dy][(int) pos_y_dy - 1] == '1')
					return (dist_tot_y + delta_y);
			dist_tot_y += delta_y;
		}
	}
}
