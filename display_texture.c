/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:02:49 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/11 15:39:52 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "display.h"
#include <stdio.h>

static void	init_texture(double *hit, t_display *dis, t_raycasting *ray, \
t_cube *cube);
static int	reverse_nbr(int nbr);
static int	**fill_texture_content(t_cube *cube, t_image texture);

void	display_texture(int *h, t_display *dis, t_raycasting *ray, t_cube *cube)
{
	int		high;
	double	hit;

	init_texture(&hit, dis, ray, cube);
	dis->text_array = fill_texture_content(cube, *dis->text);
	high = 0;
	while (*h <= dis->end && *h <= WIN_H)
	{
		if (*h % dis->lin == 0 && high + 1 < dis->text->height)
		{
			high++;
			dis->color = encodage_couleur(dis->pix);
		}
		mlx_pixel_put(cube->mlx, cube->win, ray->i, *h, \
		dis->text_array[high][dis->col]);
		*h += 1;
	}
	*h -= 1;
}

static void	init_texture(double *hit, t_display *dis, t_raycasting *ray, \
t_cube *cube)
{
	if (ray->type == 0)
		*hit = ray->pos.y + ray->perp * ray->ray_dir.y;
	else
		*hit = ray->pos.x + ray->perp * ray->ray_dir.x;
	if (ray->type == 0 && ray->ray_dir.y > 0)
		dis->text = &cube->ea;
	else if (ray->type == 0 && ray->ray_dir.y < 0)
		dis->text = &cube->we;
	else if (ray->type == 1 && ray->ray_dir.x > 0)
		dis->text = &cube->so;
	else
		dis->text = &cube->no;
	dis->decimal = modf(*hit, &dis->entier);
	dis->col = dis->text->width * dis->decimal;
	dis->lin = (dis->end - dis->start) / dis->text->height;
}

static int	reverse_nbr(int nbr)
{
	int	swap;
	int	i;

	if (nbr > 0)
		return (nbr);
	swap = 0;
	i = 0;
	while (i < 8)
	{
		if ((nbr & (1 << i)) != 0)
			swap |= 1 << ((8 - 1) - i);
		i++;
	}
	return (swap);
}

static int	**fill_texture_content(t_cube *cube, t_image texture)
{
	int	**texture_array;
	int	y;
	int	x;

	texture_array = malloc(sizeof(int *) * (texture.height));
	if (texture_array == NULL)
		return (error(MALLOC, CONT), NULL);
	y = -1;
	while (++y < texture.height)
	{
		texture_array[y] = malloc(sizeof(int) * (texture.width));
		if (texture_array[y] == NULL)
		{
			y = 0;
			while (texture_array[y] != NULL)
				free(texture_array[y++]);
			return (free(texture_array), error(MALLOC, CONT), NULL);
		}
	}
	y = 0;
	while (y < texture.height)
	{
		x = 0;
		while (x < texture.width)
		{
			texture_array[y][x] = *(int *)(texture.img + \
				(y * texture.size + x * (texture.bits / 8)));
			x++;
		}
		y++;
	}
	return (texture_array);
}
