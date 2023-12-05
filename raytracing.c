/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:17:11 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/05 19:48:59 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "display.h"
#include <stdio.h>

static double	calc_dist_max(void);
static double	collision_nord(t_raytracing *ray, double x, double y, char **map);
static void		affichage_mur(t_raytracing *ray, t_cube *cube);
static int		encodage_couleur(t_color col);
// static void		display_texture(int h, t_raytracing *ray, t_cube *cube);
// static void		my_mlx_pixel_put(t_img_data *img_data, int x, int y, int color);

void	raytracing(t_cube *cube)
{
	t_raytracing	ray;

	if (cube->personnage.orient == NORD)
		ray.begin_corner = M_PI / 2.0;
	else if (cube->personnage.orient == SUD)
		ray.begin_corner = - (M_PI / 2.0);
	else if (cube->personnage.orient == EST)
		ray.begin_corner = 0;
	else if (cube->personnage.orient == OUEST)
		ray.begin_corner = M_PI;

	ray.fov = M_PI / 8;
	ray.mini_corner = ray.begin_corner - ray.fov;
	ray.maxi_corner = ray.begin_corner + ray.fov;

	ray.dif = ray.maxi_corner - ray.mini_corner;
	ray.dif = (ray.dif / WIN_W) * 5;
	ray.corner_col = ray.mini_corner;
	ray.dist_max = calc_dist_max();
	ray.i = 0;
	while (ray.corner_col < ray.maxi_corner)
	{
		ray.dist = collision_nord(&ray, cube->personnage.x + 0.5, cube->personnage.y + 0.5, cube->map);
		if (ray.dist == -1)
			return ;
		affichage_mur(&ray, cube);
		free(ray.col);
		ray.corner_col += ray.dif;
		ray.i += 5;
	}
	mlx_loop(cube->mlx);
}

static double	collision_nord(t_raytracing *ray, double x, double y, char **map)
{
	t_collision	*col;

	col = (t_collision *) malloc(sizeof(t_collision));
	if (col == NULL)
		return (error(MALLOC, CONT), -1);
	ray->col = col;
	col->pos_x_dx = x;
	col->pos_y_dx = y;
	col->pos_x_dy = x;
	col->pos_y_dy = y;
	col->dist_tot_x = 0;
	col->dist_tot_y = 0;
	col->dif_x = 0.5;
	col->dif_y = 0.5;

	col->unknown = (col->dif_x) / tan(ray->corner_col);
	col->dist_x = sqrt(col->dif_x * col->dif_x + col->unknown * col->unknown);
	col->unknown = col->dif_y * tan(ray->corner_col);
	col->dist_y = sqrt(col->dif_y * col->dif_y + col->unknown * col->unknown);
	col->unknown = 1 / tan(ray->corner_col);
	col->delta_x = sqrt(col->unknown * col->unknown + 1);
	col->unknown = tan(ray->corner_col);
	col->delta_y = sqrt(col->unknown * col->unknown + 1);
	while (1)
	{
		if (col->dist_tot_x == 0 && ((col->dist_tot_y == 0 && \
		col->dist_tot_x + col->dist_x <= col->dist_tot_y + col->dist_y) || \
		(col->dist_tot_y != 0 && \
		col->dist_tot_x + col->dist_x <= col->dist_tot_y + col->delta_y))) // Travail sur x
		{
			col->pos_x_dx = x - (sin(ray->corner_col) * col->dist_x);
			col->pos_y_dx = y + (cos(ray->corner_col) * col->dist_x);
			col->final_x = col->pos_x_dx;
			col->final_y = col->pos_y_dx;
			if (map[((int) col->pos_x_dx) - 1][(int) col->pos_y_dx] == '1')
				return (col->dist_x);
			col->dist_tot_x = col->dist_x;
		}
		else if (col->dist_tot_y == 0 && ((col->dist_tot_x == 0 && \
		col->dist_tot_x + col->dist_x > col->dist_tot_y + col->dist_y) || \
		(col->dist_tot_x != 0 && \
		col->dist_tot_x + col->delta_x > col->dist_tot_y + col->dist_y))) // Travail sur y
		{
			col->pos_x_dy = x - (sin(ray->corner_col) * col->dist_y);
			col->pos_y_dy = y + (cos(ray->corner_col) * col->dist_y);
			col->final_x = col->pos_x_dy;
			col->final_y = col->pos_y_dy;
			if (ray->corner_col < M_PI / 2)
			{
				if (map[(int) col->pos_x_dy][((int) col->pos_y_dy)] == '1')
					return (col->dist_y);
			}
			else
			{
				if ((int) col->pos_y_dy == 0)
				{
					if (map[(int) col->pos_x_dy][(int) col->pos_y_dy] == '1')
						return (col->dist_y);
				}
				else
					if (map[(int) col->pos_x_dy][(int) col->pos_y_dy - 1] == '1')
						return (col->dist_y);
			}
			col->dist_tot_y = col->dist_y;
		}
		else if (col->dist_tot_x != 0 && ((col->dist_tot_y == 0 && \
		col->dist_tot_x + col->delta_x <= col->dist_tot_y + col->dist_y) || \
		(col->dist_tot_y != 0 && \
		col->dist_tot_x + col->delta_x <= col->dist_tot_y + col->delta_y)))
		{
			col->pos_x_dx -= 1;
			col->pos_y_dx += (cos(ray->corner_col) * col->delta_x);
			col->final_x = col->pos_x_dx;
			col->final_y = col->pos_y_dx;
			if (map[(int) col->pos_x_dx - 1][(int) col->pos_y_dx] == '1')
				return (col->dist_tot_x + col->delta_x);
			col->dist_tot_x += col->delta_x;
		}
		else if (col->dist_tot_y != 0 && ((col->dist_tot_x == 0 && \
		col->dist_tot_x + col->dist_x > col->dist_tot_y + col->delta_y) || \
		(col->dist_tot_x != 0 && \
		col->dist_tot_x + col->delta_x > col->dist_tot_y + col->delta_y)))
		{
			col->pos_x_dy -= sin(ray->corner_col) * col->delta_y;
			if (ray->corner_col < M_PI / 2)
				col->pos_y_dy += 1;
			else
				col->pos_y_dy -= 1;
			col->final_x = col->pos_x_dy;
			col->final_y = col->pos_y_dy;
			if (ray->corner_col < M_PI / 2)
			{
				if (map[(int) col->pos_x_dy][((int) col->pos_y_dy)] == '1')
					return (col->dist_tot_y + col->delta_y);
			}
			else
			{
				if ((int) col->pos_y_dy == 0)
				{
					if (map[(int) col->pos_x_dy][(int) col->pos_y_dy] == '1')
						return (col->dist_tot_y + col->delta_y);
				}
				else
					if (map[(int) col->pos_x_dy][(int) col->pos_y_dy - 1] == '1')
						return (col->dist_tot_y + col->delta_y);
			}
			col->dist_tot_y += col->delta_y;
		}
	}
}

static double	calc_dist_max(void)
{
	double	x1;
	double	x2;

	x1 = (((YARD * WIN_H) + WALL) + \
	sqrt(pow(YARD * WIN_H, 2) + ((WALL * 2) * YARD * WIN_H) + pow(WALL, 2))) / \
	(2 * WIN_H);
	x2 = (((YARD * WIN_H) + WALL) - \
	sqrt(pow(YARD * WIN_H, 2) + ((WALL * 2) * YARD * WIN_H) + pow(WALL, 2))) / \
	(2 * WIN_H);
	return (fmax(x1, x2));
}

static void	affichage_mur(t_raytracing *ray, t_cube *cube)
{
	int			h;
	t_display	dis;

	dis.c = encodage_couleur(cube->c);
	dis.f = encodage_couleur(cube->f);
	dis.wall = ((ray->dist_max - ray->dist) * WIN_H) / ray->dist_max;
	h = 0;
	while (h < WIN_H)
	{
		if (h < (WIN_H / 2) - (dis.wall / 2))
		{
			mlx_pixel_put(cube->mlx, cube->win, ray->i - 2, h, dis.c);
			mlx_pixel_put(cube->mlx, cube->win, ray->i - 1, h, dis.c);
			mlx_pixel_put(cube->mlx, cube->win, ray->i, h, dis.c);
			mlx_pixel_put(cube->mlx, cube->win, ray->i + 1, h, dis.c);
			mlx_pixel_put(cube->mlx, cube->win, ray->i + 2, h, dis.c);
		}
		else if (h > (WIN_H / 2) + (dis.wall / 2))
		{
			mlx_pixel_put(cube->mlx, cube->win, ray->i - 2, h, dis.f);
			mlx_pixel_put(cube->mlx, cube->win, ray->i - 1, h, dis.f);
			mlx_pixel_put(cube->mlx, cube->win, ray->i, h, dis.f);
			mlx_pixel_put(cube->mlx, cube->win, ray->i + 1, h, dis.f);
			mlx_pixel_put(cube->mlx, cube->win, ray->i + 2, h, dis.f);
		}
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

// static void	display_texture(int h, t_raytracing *ray, t_cube *cube)
// {
// 	double	entier;
// 	double	frac;

// 	while (ray->corner_col > M_PI)
// 		ray->corner_col -= 2 * M_PI;
// 	while (ray->corner_col <= - M_PI)
// 		ray->corner_col += 2 * M_PI;

// 	frac = modf(ray->col->final_y, &entier);
// 	printf("nbr = %f, frac = %f, entier = %f\n", ray->col->final_y, frac, entier);
// 	// if (ray->corner_col > - M_PI && ray->corner_col <= - (M_PI / 2))
// 	// else if (ray->corner_col > - (M_PI / 2) && ray->corner_col <= 0)
// 	// else if (ray->corner_col > 0 && ray->corner_col <= (M_PI / 2))
// 	// else if (ray->corner_col > (M_PI / 2) && ray->corner_col <= M_PI)
// }

// static void	my_mlx_pixel_put(t_img_data *img_data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = img_data->addr + (y * img_data->line_length + \
x * (img_data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }
