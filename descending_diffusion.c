/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descending_diffusion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:22:50 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/21 18:49:00 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	ascending_ordinate(long long int i, long long int *j, \
const size_t y, char **dup);
static int	descending_ordinate(long long int i, long long int *j, \
const size_t y, char **dup);

void	descending_diffusion(long long int i, long long int *j, \
const size_t y, char **dup)
{
	int	flag;

	flag = 0;
	while (--i >= 0 && flag != 3)
	{
		if (flag != 1)
			flag += ascending_ordinate(i, j, y, dup);
		if (flag != 2)
			flag += descending_ordinate(i, j, y, dup);
	}
}

static int	ascending_ordinate(long long int i, long long int *j, \
const size_t y, char **dup)
{
	int	flag;

	flag = 0;
	*j = ((long long int) y) - 1;
	while (*j < (long long int) ft_strlen(dup[i]) && dup[i][++(*j)])
	{
		if (dup[i][*j] == '1')
			flag = 1;
		if (dup[i][*j] == 'I')
			return (1 - flag);
		fill_dup(i, *j, dup);
		if (dup[i][*j] == 'X' && dup[i + 1] != NULL && *j > 0 && \
		dup[i + 1][*j - 1] == '1' && *j != (long long int) y)
		{
			if ((dup[i + 1] != NULL && dup[i + 1][*j] == '0'))
				diffusion(((size_t) i) + 1, (size_t)(*j), dup);
			else if (*j > 0 && dup[i][*j - 1] == '0')
				diffusion(((size_t) i), (size_t)(*j) - 1, dup);
		}
	}
	return (0);
}

static int	descending_ordinate(long long int i, long long int *j, \
const size_t y, char **dup)
{
	int	flag;

	flag = 0;
	*j = (long long int) y;
	while (*j > (long long int) ft_strlen(dup[i]))
		(*j)--;
	while (--(*j) >= 0)
	{
		if (dup[i][*j] == '1')
			flag = 2;
		if (dup[i][*j] == 'I')
			return (2 - flag);
		fill_dup(i, *j, dup);
		if (dup[i][*j] == 'X' && dup[i + 1] != NULL && \
		*j + 1 < (long long int) ft_strlen(dup[i - 1]) && \
		dup[i + 1][*j + 1] == '1')
		{
			if ((dup[i + 1] != NULL && dup[i + 1][*j] == '0'))
				diffusion(((size_t) i) + 1, (size_t)(*j), dup);
			else if (dup[i][*j] != '\0' && dup[i][*j + 1] == '0')
				diffusion(((size_t) i), (size_t)(*j) + 1, dup);
		}
	}
	return (0);
}
