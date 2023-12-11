/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:17:11 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/11 18:36:24 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

static void	fill_vector(t_vector *v, double fst, double sec);
static int	encodage_couleur(t_color col);

void	raycasting(t_cube *cube)
{
	t_raycasting	ray;

	ray.c = encodage_couleur(cube->c);
	ray.f = encodage_couleur(cube->f);
	fill_vector(&ray.dir, 0.0, 1.0);
	fill_vector(&ray.pla, 0.8, 0.0);
	if (cube->personnage.orient == NORD)
	{
		rotate_vector(&ray.dir, 90);
		rotate_vector(&ray.pla, 90);
	}
	else if (cube->personnage.orient == SUD)
	{
		rotate_vector(&ray.dir, -90);
		rotate_vector(&ray.pla, -90);
	}
	else if (cube->personnage.orient == OUEST)
	{
		rotate_vector(&ray.dir, 180);
		rotate_vector(&ray.pla, 180);
	}
	fill_vector(&ray.pos, ((double) cube->personnage.x) + 0.5, \
	((double) cube->personnage.y) + 0.5);
	collision(&ray, cube);
}

static void	fill_vector(t_vector *v, double fst, double sec)
{
	v->x = fst;
	v->y = sec;
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
