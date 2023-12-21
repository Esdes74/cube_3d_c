/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:35:58 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/21 18:49:38 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "key_events.h"

#include <stdio.h>

static int	key_down(int keycode, t_key_event *key);
static int	key_up(int keycode, t_key_event *key);
static int	quit(t_key_event *key);

void	key_events(t_raycasting *ray, t_cube *cube)
{
	t_key_event	*key;

	key = malloc(sizeof(t_key_event));
	if (key == NULL)
		return (free_all(cube), error(MALLOC, END));
	key->cube = cube;
	key->ray = ray;
	key->rot = 0;
	key->up = 0;
	key->lat = 0;
	mlx_hook(cube->win, KEY_DOWN, 1L << 0, key_down, key);
	mlx_hook(cube->win, KEY_UP, 1L << 1, key_up, key);
	mlx_hook(cube->win, BUTTON_PRESSED, 1L << 2, quit, key);
	mlx_loop_hook(cube->mlx, loop, key);
}

static int	key_down(int keycode, t_key_event *key)
{
	if (keycode == k_esc)
		quit(key);
	else if (keycode == k_le || keycode == k_q)
		key->rot = 1;
	else if (keycode == k_ri || keycode == k_e)
		key->rot = -1;
	else if (keycode == k_w)
		key->up = 1;
	else if (keycode == k_s)
		key->up = -1;
	else if (keycode == k_a)
		key->lat = -1;
	else if (keycode == k_d)
		key->lat = 1;
	return (0);
}

static int	key_up(int keycode, t_key_event *key)
{
	if (keycode == k_esc)
		quit(key);
	else if (keycode == k_le || keycode == k_q)
		key->rot = 0;
	else if (keycode == k_ri || keycode == k_e)
		key->rot = 0;
	else if (keycode == k_w)
		key->up = 0;
	else if (keycode == k_s)
		key->up = 0;
	else if (keycode == k_a)
		key->lat = 0;
	else if (keycode == k_d)
		key->lat = 0;
	return (0);
}

static int	quit(t_key_event *key)
{
	free_all(key->cube);
	free(key);
	exit(0);
	return (0);
}
