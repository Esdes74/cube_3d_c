/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffusion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:34:42 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/22 20:10:19 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	diffusion(const size_t x, const size_t y, char **dup)
{
	long long int	i;
	long long int	j;
	t_point			p;

	p.x = x;
	p.y = y;
	i = (long long int) x - 1;
	dup[x][y] = 'x';
	ascending_diffusion(i, &j, &p, dup);
	i = (long long int) x;
	descending_diffusion(i, j, y, dup);
}
