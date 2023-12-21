/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:41:23 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/21 19:02:55 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_events.h"

static void	rotate(int rot, t_raycasting *ray);
static void	forward(int forw, t_raycasting *ray);
static void	side(int side, t_raycasting *ray);

int	loop(t_key_event *key)
{
	rotate(SPEED_ROT * key->rot, key->ray);
	forward(key->up, key->ray);
	side(key->lat, key->ray);
	collision(key->ray, key->cube);
	return (0);
}

static void	rotate(int rot, t_raycasting *ray)
{
	rotate_vector(&ray->dir, rot);
	rotate_vector(&ray->pla, rot);
}

static void	forward(int forw, t_raycasting *ray)
{
	if (ray->pos.x + SPEED * forw * ray->dir.x >= 0)
		ray->pos.x += SPEED * forw * ray->dir.x;
	if (ray->pos.y + SPEED * forw * ray->dir.y >= 0)
		ray->pos.y += SPEED * forw * ray->dir.y;
}

static void	side(int side, t_raycasting *ray)
{
	t_vector	sideway;

	fill_vector(&sideway, ray->dir.x, ray->dir.y);
	rotate_vector(&sideway, 90 * side);
	if (ray->pos.x + SPEED * side * sideway.x >= 0)
		ray->pos.x += SPEED * side * sideway.x;
	if (ray->pos.y + SPEED * side * sideway.y >= 0)
		ray->pos.y += SPEED * side * sideway.y;
}
