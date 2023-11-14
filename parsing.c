/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:40:33 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/13 10:36:25 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	check_arg(char *av, t_cube *cube);
static void	check_file(int fd, t_cube *cube);
static void	check_map(int fd, t_cube *cube);

void	parsing(char *av, t_cube *cube)
{
	int	fd;

	fd = check_arg(av);
	check_file(fd, cube);
	check_map(fd, cube);
	close(fd);
}

static int	check_arg(char *av)
{
	int	i;
	int	fd;

	i = 0;
	while (av[i++])
		i++;
	if (i <= 3 || av[i - 1] != 'b' || av[i - 2] != 'u' || av[i - 3] != 'c' ||\
	av[i - 4] != '.')
		error(EXTENSION);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		error(OPEN);
	return (fd);
}

static void	check_file(int fd, t_cube *cube)
{
	int		count;
	char	*line;

	count = 6;
	line = get_next_line(fd);
	while (count > 0)
	{
		if (line == '\0')
		{
			free_all();
			if 
		}
	}
}

static void	check_map(int fd, t_cube *cube)
{

}
