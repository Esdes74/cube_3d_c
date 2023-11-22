/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:41:26 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/22 19:36:40 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	**duplicate_map(const int size, char **map);
static int	check_diffusion(char **map, char **dup);
static int	check_conditions(size_t x, size_t y, char **map, char **dup);

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

static char	**duplicate_map(const int size, char **map)
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
			if (check_conditions(x, y, map, dup))
				return (1);
		}
	}
	return (0);
}

static int	check_conditions(size_t x, size_t y, char **map, char **dup)
{
	if (map[x][y] == ' ' && dup[x][y] == 'X')
	{
		if (map[x + 1] != NULL && map[x][y + 1] != '\0' && \
		map[x][y + 1] != '\n')
			return (free_db_array(dup), error(UNVALID_SPACE, CONT), 1);
		return (free_db_array(dup), error(OPENED_MAP, CONT), 1);
	}
	else if ((map[x][y] == '\n' || map[x][y] == '\0') && \
	((dup[x][y] != '\0' && dup[x][y + 1] == 'X') \
	|| (y > 0 && dup[x][y - 1] == 'X') \
	|| (dup[x + 1] != NULL && ft_strlen(dup[x + 1]) >= y \
		&& dup[x + 1][y] == 'X') \
	|| (x > 0 && ft_strlen(dup[x - 1]) >= y && dup[x - 1][y] == 'X')))
		return (free_db_array(dup), error(OPENED_MAP, CONT), 1);
	else if ((x == 0 && map[x][y] == '0') \
	|| (y == 0 && map[x][y] == '0' && dup[x][y + 1] == 'X'))
		return (free_db_array(dup), error(OPENED_MAP, CONT), 1);
	else if (dup[x + 1] == NULL && map[x][y] == '0')
		return (free_db_array(dup), error(OPENED_MAP, CONT), 1);
	return (0);
}
