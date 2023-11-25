/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:17:11 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/24 18:30:30 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

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

	fov = M_PI / 4;
	angle_mini = angle_principale - fov;
	angle_maxi = angle_principale + fov;

	dif = angle_maxi - angle_mini;
	dif = dif / WIN_W;
	test = angle_mini;
	i = 0;
	mlx_string_put(cube->mlx, cube->win, cube->personnage.y * 30, cube->personnage.x * 30, 1000000222, "X");
	while (test < angle_maxi)
	{
		mlx_pixel_put(cube->mlx, cube->win, cube->personnage.y * 30 + cos(test) * 300, cube->personnage.x * 30 + sin(test) * 300, 1000000222);
		test += dif;
		i++;
	}
	ft_printf_fd(2, "i = %d\n", i);
	mlx_loop(cube->mlx);
}
