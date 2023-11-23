/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascending_diffusion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:45:21 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/23 14:34:20 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	ascending_ordinate(long long int i, long long int *j, \
const t_point *p, char **dup);
static int	descending_ordinate(long long int i, \
long long int *j, const size_t x, char **dup);

void	ascending_diffusion(long long int i, long long int *j, \
const t_point *p, char **dup)
{
	int	flag;

	flag = 0;
	while (dup[++i] && flag != 3)
	{
		if (flag != 1)
			flag += ascending_ordinate(i, j, p, dup);
		*j = (long long int) p->y;
		while (*j > (long long int) ft_strlen(dup[i]))
			(*j)--;
		if (flag != 2)
			flag += descending_ordinate(i, j, p->x, dup);
	}
}

static int	ascending_ordinate(long long int i, long long int *j, \
const t_point *p, char **dup)
{
	int	flag;

	flag = 0;
	*j = ((long long int) p->y) - 1;
	if ((size_t) i == p->x && (size_t)(*j) + 1 == p->y)
		(*j)++;
	while (*j < (long long int) ft_strlen(dup[i]) && dup[i][++(*j)])
	{
		if (dup[i][*j] == '1')
			flag = 1;
		if (dup[i][*j] == 'I')
			return (1 - flag);
		fill_dup(i, *j, dup);
		if (dup[i][*j] == 'X' && i > 0 && *j > 0 && dup[i - 1][*j - 1] == '1' \
		&& i != (long long int) p->x && *j != (long long int) p->y)
		{
			if ((i > 0 && dup[i - 1][*j] == '0'))
				diffusion(((size_t) i) - 1, (size_t)(*j), dup);
			else if (*j > 0 && dup[i][*j - 1] == '0')
				diffusion(((size_t) i), (size_t)(*j) - 1, dup);
		}
	}
	return (0);
}

static int	descending_ordinate(long long int i, long long int *j, \
const size_t x, char **dup)
{
	int	flag;

	flag = 0;
	while (--(*j) >= 0)
	{
		if (dup[i][*j] == '1')
			flag = 2;
		if (dup[i][*j] == 'I')
			return (2 - flag);
		fill_dup(i, *j, dup);
		if (dup[i][*j] == 'X' && i > 0 && \
		*j + 1 < (long long int) ft_strlen(dup[i - 1]) && \
		dup[i - 1][*j + 1] == '1' && i != (long long int) x)
		{
			if ((i > 0 && dup[i - 1][*j] == '0'))
				diffusion(((size_t) i) - 1, (size_t)(*j), dup);
			else if (dup[i][*j] != '\0' && dup[i][*j + 1] == '0')
				diffusion(((size_t) i), (size_t)(*j) + 1, dup);
		}
	}
	return (0);
}
