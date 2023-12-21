/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:40:33 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/21 18:49:58 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	check_arg(const char *av, t_cube *cube);
static void	check_texture(const int fd, t_cube *cube);
static void	texture_comp(const int fd, const t_image *fst, \
const t_image *sec, t_cube *cube);

void	parsing(const char *av, t_cube *cube)
{
	int	fd;

	fd = check_arg(av, cube);
	check_file(fd, cube);
	encodage_texture(fd, cube);
	check_texture(fd, cube);
	check_map(fd, cube);
	close(fd);
	verif_map(cube);
}

static int	check_arg(const char *av, t_cube *cube)
{
	int	i;
	int	fd;

	i = 0;
	while (av[i])
		i++;
	if (i <= 3 || av[i - 1] != 'b' || av[i - 2] != 'u' || av[i - 3] != 'c'\
	|| av[i - 4] != '.')
		return (free_all(cube), error(EXTENSION, END), -1);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (free_all(cube), error(OPEN, END), -1);
	return (fd);
}

static void	check_texture(const int fd, t_cube *cube)
{
	texture_comp(fd, &cube->no, &cube->so, cube);
	texture_comp(fd, &cube->no, &cube->we, cube);
	texture_comp(fd, &cube->no, &cube->ea, cube);
	texture_comp(fd, &cube->so, &cube->we, cube);
	texture_comp(fd, &cube->so, &cube->ea, cube);
	texture_comp(fd, &cube->we, &cube->ea, cube);
}

static void	texture_comp(const int fd, const t_image *fst, const t_image *sec, \
t_cube *cube)
{
	int	x;
	int	y;

	if (fst->width != sec->width)
		return ;
	if (fst->height != sec->height)
		return ;
	if (fst->bits != sec->bits)
		return ;
	if (fst->size != sec->size)
		return ;
	x = -1;
	while ((++x) < fst->height)
	{
		y = -1;
		while ((++y) < fst->width)
		{
			if (ft_strncmp(&fst->img[(x * fst->size) + (y * fst->bits)], \
			&sec->img[(x * fst->size) + (y * sec->bits)], fst->bits) != 0)
				return ;
		}
	}
	close(fd);
	free_all(cube);
	error(SAME_TEXTURE, END);
}
