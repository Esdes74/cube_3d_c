/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:02:49 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/11 18:34:06 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "display.h"

static void	init_texture(double *hit, t_display *dis, t_raycasting *ray, \
t_cube *cube);

void	display_texture(int *h, t_display *dis, t_raycasting *ray, t_cube *cube)
{
	int		high;
	double	hit;

	init_texture(&hit, dis, ray, cube);
	high = 0;
	while (*h <= dis->end && *h <= WIN_H)
	{
		if (*h % dis->lin == 0 && high + 1 < dis->text->height)
			high++;
		mlx_pixel_put(cube->mlx, cube->win, ray->i, *h, \
		dis->text->pix_img[high][dis->col]);
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
