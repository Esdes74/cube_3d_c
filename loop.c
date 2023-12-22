/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:41:23 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/22 11:16:00 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_events.h"

static void	rotate(int rot, t_raycasting *ray);
static void	forward(int forw, t_raycasting *ray, t_cube *cube);
static void	side(int side, t_raycasting *ray, t_cube *cube);

int	loop(t_key_event *key)
{
	rotate(SPEED_ROT * key->rot, key->ray);
	forward(key->up, key->ray, key->cube);
	side(key->lat, key->ray, key->cube);
	collision(key->ray, key->cube);
	return (0);
}

static void	rotate(int rot, t_raycasting *ray)
{
	rotate_vector(&ray->dir, rot);
	rotate_vector(&ray->pla, rot);
}

static void	forward(int forw, t_raycasting *ray, t_cube *cube)
{
	if (cube->map[(int)(ray->pos.x + SPEED * forw * ray->dir.x)] \
	[(int)(ray->pos.y + SPEED * forw * ray->dir.y)] != '1')
	{
		ray->pos.x += SPEED * forw * ray->dir.x;
		ray->pos.y += SPEED * forw * ray->dir.y;
	}
}

static void	side(int side, t_raycasting *ray, t_cube *cube)
{
	t_vector	sideway;

	fill_vector(&sideway, ray->dir.x, ray->dir.y);
	rotate_vector(&sideway, 90 * side);
	if (cube->map[(int)(ray->pos.x + SPEED * sideway.x)] \
	[(int)(ray->pos.y + SPEED * sideway.y)] != '1' && side != 0)
	{
		ray->pos.x += SPEED * sideway.x;
		ray->pos.y += SPEED * sideway.y;
	}
}
