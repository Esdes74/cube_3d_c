/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:41:26 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/16 19:50:43 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	**duplicate_map(int size, char **map);
static void	diffusion(size_t x, size_t y, char **dup);
static int	check_diffusion(char **map, char **dup);

void	verif_map(t_cube *cube)
{
	size_t	x;
	size_t	y;
	char	**dup;

	dup = duplicate_map(cube->size_map, cube->map);
	if (dup == NULL)
		return (free_all(cube), exit(1));
	x = -1;
	while (dup[++x])
	{
		y = -1;
		while (dup[x][++y])
			if (ft_in(dup[x][y], PERSO) == 1)
				break ;
		if (dup[x][y] != '\0')
			break ;
	}
	diffusion(x, y, dup);
	if (check_diffusion(cube->map, dup))
		return (free_all(cube), exit(1));
	free_db_array(dup);
}

static char	**duplicate_map(int size, char **map)
{
	char	**dup;
	int		i;

	dup = (char **) malloc(sizeof(char *) * (size + 1));
	if (dup == NULL)
		return (error(MALLOC, CONT), NULL);
	i = -1;
	while (map[++i])
	{
		dup[i] = ft_strdup(map[i]);
		if (dup[i] == NULL)
			return (free_db_array(dup), error(MALLOC, CONT), NULL);
	}
	dup[i] = NULL;
	return (dup);
}

static void	diffusion(size_t x, size_t y, char **dup)
{
	if (dup[x] == NULL || dup[x][y] == '1' || dup[x][y] == 'X' \
	|| dup[x][y] == '\n' || dup[x][y] == '\0')
		return ;
	dup[x][y] = 'X';
	diffusion(x + 1, y, dup);
	if (x > 0)
		diffusion(x - 1, y, dup);
	diffusion(x, y + 1, dup);
	if (y > 0)
		diffusion(x, y - 1, dup);
}

static int	check_diffusion(char **map, char **dup)
{
	size_t	x;
	size_t	y;

	x = -1;
	while (map[++x])
	{
		y = -1;
		while (map[x][++y])
		{
			if (map[x][y] == ' ' && dup[x][y] == 'X')
				return (free_db_array(dup), error(OPENED_MAP, CONT), 1);
			else if ((map[x][y] == '\n' || map[x][y] == '\0') && \
			((dup[x][y] != '\0' && dup[x][y + 1] == 'X') \
			|| (y > 0 && dup[x][y - 1] == 'X') \
			|| (dup[x + 1] != NULL && ft_strlen(dup[x + 1]) >= y \
				&& dup[x + 1][y] == 'X') \
			|| (x > 0 && ft_strlen(dup[x - 1]) >= y && dup[x - 1][y] == 'X')))
				return (free_db_array(dup), error(OPENED_MAP, CONT), 1);
			else if (x == 0 && map[x][y] == '0')
				return (free_db_array(dup), error(OPENED_MAP, CONT), 1);
			else if (dup[x + 1] != NULL && map[x][y] == '0')
				return (free_db_array(dup), error(OPENED_MAP, CONT), 1);
		}
	}
	return (0);
}
