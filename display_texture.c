/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estelamb <estelamb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:02:49 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/19 17:09:42 by estelamb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "display.h"

#include <stdio.h>

static void	init_texture(t_display *dis, t_raycasting *ray, \
t_cube *cube);

void	display_texture(int *h, t_display *dis, t_raycasting *ray, t_cube *cube)
{
	int	high;
	int	dep;

	init_texture(dis, ray, cube);
	high = 0;
	dep = 0; //((dis->end - dis->start) / 2) - (dis->lin * (dis->text->height / 2));
	printf("dif = %d, lin = %d\n", ((dis->end - dis->start) / 2) - (dis->lin * (dis->text->height / 2)), dis->lin);
	while (*h <= dis->end && *h <= WIN_H)
	{
		if (dep == dis->lin && high + 1 < dis->text->height)
		{
			high++;
			dep = -1;
		}
		dep++;
		mlx_pixel_put(cube->mlx, cube->win, ray->i, *h, \
		dis->text->pix_img[high][dis->col]);
		*h += 1;
	}
	*h -= 1;
}

static void	init_texture(t_display *dis, t_raycasting *ray, \
t_cube *cube)
{
	double hit;

	if (ray->type == 0)
		hit = ray->pos.y + ray->perp * ray->ray_dir.y;
	else
		hit = ray->pos.x + ray->perp * ray->ray_dir.x;
	if (ray->type == 0 && ray->ray_dir.x > 0)
		dis->text = &cube->so;
	else if (ray->type == 0 && ray->ray_dir.x < 0)
		dis->text = &cube->no;
	else if (ray->type == 1 && ray->ray_dir.y > 0)
		dis->text = &cube->ea;
	else
		dis->text = &cube->we;
	dis->decimal = modf(hit, &dis->entier);
	dis->col = dis->text->width * dis->decimal;
	dis->lin = (dis->end - dis->start) / dis->text->height;
}
