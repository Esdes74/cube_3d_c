/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:21:35 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/07 20:05:29 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "display.h"
#include <stdio.h>

static void	init_collision(int i, t_raycasting *ray);
static void	init_sdist_step(t_raycasting *ray);
static void	affichage_mur(t_raycasting *ray, t_cube *cube);
static void	display_texture(int *h, t_display *dis, t_raycasting *ray, \
t_cube *cube);

void	collision(t_raycasting *ray, t_cube *cube)
{
	ray->i = 0;
	ray->type = -1;
	while (ray->i < WIN_W)
	{
		init_collision(ray->i++, ray);
		while (ray->wall == 0)
		{
			if (ray->sdist.x < ray->sdist.y)
			{
				ray->sdist.x += ray->delta.x;
				ray->cur.x += ray->step.x;
				ray->type = 0;
			}
			else
			{
				ray->sdist.y += ray->delta.y;
				ray->cur.y += ray->step.y;
				ray->type = 1;
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
	if (ray->ray_dir.x != 0)
		ray->delta.x = fabs(1 / ray->ray_dir.x);
	else
		ray->delta.x = 1e30;
	if (ray->ray_dir.y != 0)
		ray->delta.y = fabs(1 / ray->ray_dir.y);
	else
		ray->delta.y = 1e30;
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
	t_display	dis;

	if (ray->type == 0)
		ray->perp = ray->sdist.x - ray->delta.x;
	else
		ray->perp = ray->sdist.y - ray->delta.y;
	dis.wall = WIN_H / ray->perp;
	dis.start = -dis.wall / 2 + WIN_H / 2;
	dis.end = dis.wall / 2 + WIN_H / 2;
	h = 0;
	while (h < WIN_H)
	{
		if (dis.start > 0 && h < dis.start)
			mlx_pixel_put(cube->mlx, cube->win, ray->i, h, ray->c);
		else if (dis.end < WIN_H && h > dis.end)
			mlx_pixel_put(cube->mlx, cube->win, ray->i, h, ray->f);
		else
			display_texture(&h, &dis, ray, cube);
		h++;
	}
}

static void	display_texture(int *h, t_display *dis, t_raycasting *ray, \
t_cube *cube)
{
	double	hit;
	int		H;

	if (ray->type == 0)
		hit = ray->pos.y + ray->perp * ray->ray_dir.y;
	else
		hit = ray->pos.x + ray->perp * ray->ray_dir.x;
	if (ray->type == 0 && ray->ray_dir.y > 0)
		dis->text = &cube->ea;
	else if (ray->type == 0 && ray->ray_dir.y < 0)
		dis->text = &cube->we;
	else if (ray->type == 1 && ray->ray_dir.x > 0)
		dis->text = &cube->so;
	else
		dis->text = &cube->no;
	dis->decimal = modf(hit, &dis->entier);
	dis->col = dis->text->width * dis->decimal;
	dis->lin = (dis->end - dis->start) / dis->text->height;
	H = 0;
	while (*h <= dis->end && *h <= WIN_H)
	{
		if (*h % dis->lin == 0)
		{
			H++;
			// printf("H = %d, size = %d, res = %d\n", H, dis->text->size, *h / dis->lin);
			dis->pix.blu = dis->text->img[H * dis->text->size + \
			dis->col * (dis->text->bits / 8)];
			dis->pix.gre = dis->text->img[H * dis->text->size + \
			dis->col * (dis->text->bits / 8) + 1];
			dis->pix.red = dis->text->img[H * dis->text->size + \
			dis->col * (dis->text->bits / 8) + 2];
			// printf("col = %d, blu = %d, gre = %d, red = %d\n", dis->col, dis->pix.blu, dis->pix.gre, dis->pix.red);
			printf("blu = %d, gre = %d, red = %d\n", dis->text->img[H * dis->text->size + \
			dis->col * (dis->text->bits / 8)], dis->text->img[H * dis->text->size + \
			dis->col * (dis->text->bits / 8)] + 1, dis->text->img[H * dis->text->size + \
			dis->col * (dis->text->bits / 8)] + 2);
			dis->color = encodage_couleur(dis->pix);
		}
		mlx_pixel_put(cube->mlx, cube->win, ray->i, *h, dis->color);
		*h += 1;
	}
	*h -= 1;
}
