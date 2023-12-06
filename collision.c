/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:21:35 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/06 20:06:44 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "display.h"
#include <stdio.h>

static void	init_collision(int i, t_raycasting *ray);
static void	init_sdist_step(t_raycasting *ray);
static void	affichage_mur(t_raycasting *ray, t_cube *cube);
static int	encodage_couleur(t_color col);

void	collision(t_raycasting *ray, t_cube *cube)
{
	ray->i = 0;
	while (ray->i < WIN_W)
	{
		init_collision(ray->i++, ray);
		while (ray->wall == 0)
		{
			if (ray->sdist.x < ray->sdist.y)
			{
				ray->sdist.x += ray->delta.x;
				ray->cur.x += ray->step.x;
				ray->perp = ray->sdist.x - ray->delta.x;
			}
			else
			{
				ray->sdist.y += ray->delta.y;
				ray->cur.y += ray->step.y;
				ray->perp = ray->sdist.y - ray->delta.y;
			}
			if (cube->map[ray->cur.x][ray->cur.y] == '1')
				ray->wall = 1;
		}
		affichage_mur(ray, cube);
	}
	mlx_loop(cube->mlx);
}

static void	init_collision(int i, t_raycasting *ray)
{
	ray->wall = 0;
	ray->cam_mul = (2 * i / (double) WIN_W) - 1;
	ray->ray_dir.x = ray->dir.x + ray->pla.x * ray->cam_mul;
	ray->ray_dir.y = ray->dir.y + ray->pla.y * ray->cam_mul;
	printf("ray_dir.x = %f, ", ray->ray_dir.x);
	if (ray->ray_dir.x != 0)
		ray->delta.x = fabs(1 / ray->ray_dir.x);
	else
		ray->delta.x = 1e30;
	if (ray->ray_dir.y != 0)
		ray->delta.y = fabs(1 / ray->ray_dir.y);
	else
		ray->delta.y = 1e30;
	printf("delta.x = %f, ", ray->delta.x);
	ray->cur.x = (int) ray->pos.x;
	ray->cur.y = (int) ray->pos.y;
	init_sdist_step(ray);
}

static void	init_sdist_step(t_raycasting *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->sdist.x = (ray->pos.x - ray->cur.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sdist.x = (ray->cur.x + 1.0 - ray->pos.x) * ray->delta.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->sdist.y = (ray->pos.y - ray->cur.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sdist.y = (ray->cur.y + 1.0 - ray->pos.y) * ray->delta.y;
	}
}

static void	affichage_mur(t_raycasting *ray, t_cube *cube)
{
	int			h;
	int			start;
	int			end;
	t_display	dis;

	dis.c = encodage_couleur(cube->c);
	dis.f = encodage_couleur(cube->f);
	printf("perp = %f\n", ray->perp);
	dis.wall = WIN_H / ray->perp;
	start = -dis.wall / 2 + WIN_H / 2;
	end = dis.wall / 2 + WIN_H / 2;
	h = 0;
	while (h < WIN_H)
	{
		if (start > 0 && h < start)
			mlx_pixel_put(cube->mlx, cube->win, ray->i, h, dis.c);
		else if (end < WIN_H && h > end)
			mlx_pixel_put(cube->mlx, cube->win, ray->i, h, dis.f);
		// else
		// 	display_texture(h, ray, cube);
		h++;
	}
}

static int	encodage_couleur(t_color col)
{
	int	res;

	res = 0;
	res = res | (col.red << 16);
	res = res | (col.gre << 8);
	res = res | col.blu;
	return (res);
}
