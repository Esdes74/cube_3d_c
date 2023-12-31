/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:02:49 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/21 18:49:06 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "display.h"

static void	init_texture(t_display *dis, t_raycasting *ray, \
t_cube *cube);

void	display_texture(int *h, t_display *dis, t_raycasting *ray, t_cube *cube)
{
	int	tex_y;

	init_texture(dis, ray, cube);
	while (*h <= dis->end && *h <= WIN_H)
	{
		while (dis->start < 0)
		{
			tex_y = (int) dis->text_pos;
			dis->text_pos += dis->step;
			dis->start++;
		}
		if ((int) dis->text_pos < dis->text->height)
			tex_y = (int) dis->text_pos;
		dis->text_pos += dis->step;
		put_pix(&cube->screen, dis->text->pix_img[tex_y][dis->text_x], \
		ray->i, *h);
		*h += 1;
	}
	*h -= 1;
}

static void	init_texture(t_display *dis, t_raycasting *ray, \
t_cube *cube)
{
	double	hit;

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
	hit -= floor(hit);
	dis->text_x = (int)(hit * ((double) dis->text->width));
	if ((ray->type == 0 && ray->ray_dir.x > 0) || \
	(ray->type == 1 && ray->ray_dir.y < 0))
		dis->text_x = dis->text->width - dis->text_x - 1;
	dis->lin = (int)(WIN_H / ray->perp);
	dis->step = 1.0 * dis->text->height / dis->lin;
	dis->text_pos = (dis->start - WIN_H / 2 + dis->lin / 2) * dis->step;
}
