/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:40:33 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/16 10:39:39 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	check_arg(char *av, t_cube *cube);
static void	check_file(int fd, t_cube *cube);
static int	check_image(char *line, t_cube *cube);
static int	add_img(char **spt, t_cube *cube, t_image *im);
// static void	check_map(int fd, t_cube *cube);

void	parsing(char *av, t_cube *cube)
{
	int	fd;

	fd = check_arg(av, cube);
	check_file(fd, cube);
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

static void	check_file(int fd, t_cube *cube)
{
	int		count;
	char	*line;

	count = 6;
	line = get_next_line(fd);
	while (count > 0)
	{
		while (line && line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
		}
		if (!line || line[0] == '\0')
		{
			free_all(cube);
			if (count == 6)
				return (close(fd), free(line), error(EMPTY_FILE, END));
			return (close(fd), free(line), error(UNCOMPLETE_FILE, END));
		}
		if (check_image(line, cube) == 1)
			return (close(fd), free(line), exit(1));
		free(line);
		line = get_next_line(fd);
		count--;
	}
}

static int	check_image(char *line, t_cube *cube)
{
	char	**spt;

	spt = ft_split(line, ' ');
	if (spt == NULL)
		return (free_all(cube), error(MALLOC, CONTINUE), 1);
	if (spt[0] == NULL || spt[1] == NULL || spt[2] != NULL)
		return (free_db_array(spt), free_all(cube), \
	error(TEXTURE_FORMAT, CONTINUE), 1);
	if (ft_strncmp(spt[0], "NO", 3) == 0)
		return (add_img(spt, cube, &cube->no));
	else if (ft_strncmp(spt[0], "SO", 3) == 0)
		return (add_img(spt, cube, &cube->so));
	else if (ft_strncmp(spt[0], "WE", 3) == 0)
		return (add_img(spt, cube, &cube->we));
	else if (ft_strncmp(spt[0], "EA", 3) == 0)
		return (add_img(spt, cube, &cube->ea));
	return (free_db_array(spt), error(WRONG_IDENTIFIER, CONTINUE), 1);
}

static int	add_img(char **spt, t_cube *cube, t_image *im)
{
	im->ptr_image = mlx_xpm_file_to_image(cube->mlx, spt[1], \
	&im->width, &im->height);
	if (im->ptr_image == NULL)
		return (free_db_array(spt), free_all(cube), \
	error(XPM_FILE, CONTINUE), 1);
	im->img = mlx_get_data_addr(im->ptr_image, \
	&im->bits, &im->size, &im->endian);
	if (im->img == NULL)
		return (free_db_array(spt), free_all(cube), \
	error(IMG_ADDR, CONTINUE), 1);
	free_db_array(spt);
	return (0);
}

// static void	check_map(int fd, t_cube *cube)
// {

// }
