/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:40:33 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/16 14:22:04 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	check_arg(char *av, t_cube *cube);
// static void	check_map(int fd, t_cube *cube);

void	parsing(char *av, t_cube *cube)
{
	int	fd;
	int	count;

	fd = check_arg(av, cube);
	check_file(fd, &count, cube);
	// check_map(fd, cube);
	close(fd);
}

static int	check_arg(char *av, t_cube *cube)
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

// static void	check_map(int fd, t_cube *cube)
// {

// }
