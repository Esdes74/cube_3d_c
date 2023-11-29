/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:17:11 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/29 12:01:14 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

static double	collision_nord(double test, double x, double y, char **map);

void	raytracing(t_cube *cube)
{
	double	angle_principale;

	if (cube->personnage.orient == NORD)
		angle_principale = M_PI / 2.0;
	else if (cube->personnage.orient == SUD)
		angle_principale = - (M_PI / 2.0);
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
	double	save;

	fov = M_PI / 4;
	angle_mini = angle_principale - fov;
	angle_maxi = angle_principale + fov;

	dif = angle_maxi - angle_mini;
	dif = dif / WIN_W;
	test = angle_mini;
	i = 0;
	save = 0;
	// dist = collision_nord((5.0 * M_PI) / 8.0, cube->personnage.x + 0.5, cube->personnage.y + 0.5, cube->map);
	mlx_string_put(cube->mlx, cube->win, cube->personnage.y * 100, cube->personnage.x * 100, 1000000222, "X");
	while (test < angle_maxi)
	{
		dist = collision_nord(test, cube->personnage.x + 0.5, cube->personnage.y + 0.5, cube->map);
		if (dist > save + 1 || dist < save - 1)
			printf("test = %lf, dist = %lf\n", test, dist);
		save = dist;
		mlx_pixel_put(cube->mlx, cube->win, (int) ((double) cube->personnage.y * 100.0) + (cos(test) * dist * 20), (int) ((double) cube->personnage.x * 100.0) - (sin(test) * dist * 20), 1000000222);
		test += dif;
		i++;
	}
	ft_printf_fd(2, "\ni = %d\n", i);
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
	// printf("unknown = %lf, dist_x = %lf\n", unknown, dist_x);
	unknown = dif_y * tan(test);
	dist_y = sqrt(dif_y * dif_y + unknown * unknown);
	// printf("unknown = %lf, dist_y = %lf\n", unknown, dist_y);
	unknown = 1 / tan(test);
	delta_x = sqrt(unknown * unknown + 1);
	// printf("unknown = %lf, delta_x = %lf\n", unknown, delta_x);
	unknown = tan(test);
	delta_y = sqrt(unknown * unknown + 1);
	// printf("unknown = %lf, delta_y = %lf\n", unknown, delta_y);
	while (1)
	{
		if (dist_tot_x == 0 && ((dist_tot_y == 0 && \
		dist_tot_x + dist_x <= dist_tot_y + dist_y) || \
		(dist_tot_y != 0 && \
		dist_tot_x + dist_x <= dist_tot_y + delta_y))) // Travail sur x
		{
			// printf("A");
			pos_x_dx = x - (sin(test) * dist_x);
			pos_y_dx = y + (cos(test) * dist_x);
			// printf("x = %lf, y = %lf, (cos(test) * dist_x) = %lf\n", pos_x_dx, pos_y_dx, (cos(test) * dist_x));
			if (map[((int) pos_x_dx) - 1][(int) pos_y_dx] == '1')
				return (dist_x);
			dist_tot_x = dist_x;
		}
		else if (dist_tot_y == 0 && ((dist_tot_x == 0 && \
		dist_tot_x + dist_x > dist_tot_y + dist_y) || \
		(dist_tot_x != 0 && \
		dist_tot_x + delta_x > dist_tot_y + dist_y))) // Travail sur y
		{
			// printf("B");
			pos_x_dy = x - (sin(test) * dist_y);
			pos_y_dy = y + (cos(test) * dist_y);
			// printf("x = %d, y = %d, test = %lf\n", (int) pos_x_dy, (int) pos_y_dy, test);
			if (test < M_PI / 2)
			{
				if (map[(int) pos_x_dy][((int) pos_y_dy)] == '1')
					return (dist_y);
			}
			else
			{
				if ((int) pos_y_dy == 0)
				{
					if (map[(int) pos_x_dy][(int) pos_y_dy] == '1')
						return (dist_y);
				}
				else
					if (map[(int) pos_x_dy][(int) pos_y_dy - 1] == '1')
						return (dist_y);
			}
			dist_tot_y = dist_y;
		}
		else if (dist_tot_x != 0 && ((dist_tot_y == 0 && \
		dist_tot_x + delta_x <= dist_tot_y + dist_y) || \
		(dist_tot_y != 0 && \
		dist_tot_x + delta_x <= dist_tot_y + delta_y)))
		{
			// printf("C");
			pos_x_dx -= 1;
			pos_y_dx += (cos(test) * delta_x);
			if (test == M_PI / 2)
				printf("yes\n");
			// printf("x = %lf, y = %lf, (cos(test) * delta_x) = %lf", pos_x_dx, pos_y_dx, (cos(test) * delta_x));
			if (map[(int) pos_x_dx - 1][(int) pos_y_dx] == '1')
				return (dist_tot_x + delta_x);
			dist_tot_x += delta_x;
		}
		else if (dist_tot_y != 0 && ((dist_tot_x == 0 && \
		dist_tot_x + dist_x > dist_tot_y + delta_y) || \
		(dist_tot_x != 0 && \
		dist_tot_x + delta_x > dist_tot_y + delta_y)))
		{
			// printf("D");
			pos_x_dy -= sin(test) * delta_y;
			if (test < M_PI / 2)
				pos_y_dy += 1;
			else
				pos_y_dy -= 1;
			// printf("x = %lf, y = %d\n", pos_x_dy, (int) pos_y_dy);
			if (test < M_PI / 2)
			{
				if (map[(int) pos_x_dy][((int) pos_y_dy)] == '1')
					return (dist_tot_y + delta_y);
			}
			else
			{
				if ((int) pos_y_dy == 0)
				{
					if (map[(int) pos_x_dy][(int) pos_y_dy] == '1')
						return (dist_tot_y += delta_y);
				}
				else
					if (map[(int) pos_x_dy][(int) pos_y_dy - 1] == '1')
						return (dist_tot_y += delta_y);
			}
			dist_tot_y += delta_y;
		}
	}
}
