/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descending_diffusion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:22:50 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/22 19:29:36 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	ascending_ordinate(long long int i, long long int j, \
const size_t y, char **dup);
static void	descending_ordinate(long long int i, long long int j, \
const size_t y, char **dup);

void	descending_diffusion(long long int i, long long int j, \
const size_t y, char **dup)
{
	while (--i >= 0)
	{
		ascending_ordinate(i, j, y, dup);
		if (dup[i][j] == 'x')
			break ;
		descending_ordinate(i, j, y, dup);
		if (j >= 0 && dup[i][j] == 'x')
			break ;
	}
}

static void	ascending_ordinate(long long int i, long long int j, \
const size_t y, char **dup)
{
	j = ((long long int) y) - 1;
	while (j < (long long int) ft_strlen(dup[i]) && dup[i][++j])
	{
		if (dup[i][j] == 'x')
			break ;
		fill_dup(i, j, dup);
		if (dup[i][j] == 'X' && dup[i + 1] != NULL && j > 0 && \
		dup[i + 1][j - 1] == '1')
		{
			if ((dup[i + 1] != NULL && dup[i + 1][j] == '0'))
				diffusion(((size_t) i) - 1, (size_t) j, dup);
			else if (j > 0 && dup[i][j - 1] == '0')
				diffusion(((size_t) i), (size_t) j - 1, dup);
		}
	}
}

static void	descending_ordinate(long long int i, long long int j, \
const size_t y, char **dup)
{
	j = (long long int) y;
	while (--j >= 0)
	{
		if (dup[i][j] == 'x')
			break ;
		fill_dup(i, j, dup);
		if (dup[i][j] == 'X' && dup[i + 1] != NULL && \
		j + 1 > (long long int) ft_strlen(dup[i - 1]) && \
		dup[i + 1][j + 1] == '1')
		{
			if ((dup[i + 1] != NULL && dup[i + 1][j] == '0'))
				diffusion(((size_t) i) - 1, (size_t) j, dup);
			else if (dup[i][j] != '\0' && dup[i][j + 1] == '0')
				diffusion(((size_t) i), (size_t) j + 1, dup);
		}
	}
}
