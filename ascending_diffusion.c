/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascending_diffusion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:45:21 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/22 19:22:21 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	ascending_ordinate(long long int i, long long int j, \
const t_point *p, char **dup);
static void	descending_ordinate(long long int i, \
long long int j, char **dup);

void	ascending_diffusion(long long int i, long long int *j, \
const t_point *p, char **dup)
{
	while (dup[++i])
	{
		ascending_ordinate(i, *j, p, dup);
		if (*j < (long long int) ft_strlen(dup[i]) && dup[i][*j] == 'x')
			break ;
		*j = (long long int) p->y;
		while (*j >= (long long int) ft_strlen(dup[i]))
			(*j)--;
		descending_ordinate(i, *j, dup);
		if (*j >= 0 && dup[i][*j] == 'x')
			break ;
	}
}

static void	ascending_ordinate(long long int i, long long int j, \
const t_point *p, char **dup)
{
	j = ((long long int) p->y) - 1;
	if ((size_t) i == p->x && (size_t) j + 1 == p->y)
		j++;
	while (j < (long long int) ft_strlen(dup[i]) && dup[i][++j])
	{
		if (dup[i][j] == 'x')
			break ;
		fill_dup(i, j, dup);
		if (dup[i][j] == 'X' && i > 0 && j > 0 && dup[i - 1][j - 1] == '1')
		{
			if ((i > 0 && dup[i - 1][j] == '0'))
				diffusion(((size_t) i) - 1, (size_t) j, dup);
			else if (j > 0 && dup[i][j - 1] == '0')
				diffusion(((size_t) i), (size_t) j - 1, dup);
		}
	}
}

static void	descending_ordinate(long long int i, long long int j, char **dup)
{
	while (--j >= 0)
	{
		if (dup[i][j] == 'x')
			break ;
		fill_dup(i, j, dup);
		if (dup[i][j] == 'X' && i > 0 && \
		j + 1 > (long long int) ft_strlen(dup[i - 1]) && \
		dup[i - 1][j + 1] == '1')
		{
			if ((i > 0 && dup[i - 1][j] == '0'))
				diffusion(((size_t) i) - 1, (size_t) j, dup);
			else if (dup[i][j] != '\0' && dup[i][j + 1] == '0')
				diffusion(((size_t) i), (size_t) j + 1, dup);
		}
	}
}
