/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:57:08 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/17 22:13:47 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	check_image(char *line, t_cube *cube);
static int	add_img(char **spt, t_cube *cube, t_image *im);
static int	add_color(char **spt, t_cube *cube, t_color *col);
static int	fill_rgb(int *count, t_cube *cube, t_color *col, char **rgb);

void	check_file(int fd, t_cube *cube)
{
	int		count;
	char	*line;

	count = 6;
	line = get_next_line(fd);
	while (count > 0)
	{
		line = pass_newline(fd, line);
		if (!line || line[0] == '\0')
		{
			free_all(cube);
			if (count == 6)
				return (close(fd), free(line), error(EMPTY_FILE, END));
			return (close(fd), free(line), error(UNCOMPLETE_FILE, END));
		}
		if (check_image(line, cube))
			return (close(fd), free(line), exit(1));
		free(line);
		line = get_next_line(fd);
		(count)--;
	}
	free(line);
}

static int	check_image(char *line, t_cube *cube)
{
	char	**spt;

	spt = ft_split(line, ' ');
	if (spt == NULL)
		return (free_all(cube), error(MALLOC, CONT), 1);
	if (spt[0] != NULL && ft_strncmp(spt[0], "C", 2) == 0)
		return (add_color(spt, cube, &cube->c));
	else if (spt[0] != NULL && ft_strncmp(spt[0], "F", 2) == 0)
		return (add_color(spt, cube, &cube->f));
	if (spt[0] == NULL || spt[1] == NULL || spt[2] != NULL)
		return (free_db_array(spt), free_all(cube), \
	error(TEXTURE_FORMAT, CONT), 1);
	if (ft_strncmp(spt[0], "NO", 3) == 0)
		return (add_img(spt, cube, &cube->no));
	else if (ft_strncmp(spt[0], "SO", 3) == 0)
		return (add_img(spt, cube, &cube->so));
	else if (ft_strncmp(spt[0], "WE", 3) == 0)
		return (add_img(spt, cube, &cube->we));
	else if (ft_strncmp(spt[0], "EA", 3) == 0)
		return (add_img(spt, cube, &cube->ea));
	return (free_db_array(spt), free_all(cube), \
	error(WRONG_IDENTIFIER, CONT), 1);
}

static int	add_img(char **spt, t_cube *cube, t_image *im)
{
	size_t	i;

	if (im->ptr_image != NULL)
		return (free_db_array(spt), free_all(cube), \
	error(DB_TEXTURE_IDENTIFIER, CONT), 1);
	i = 0;
	while (spt[1][i] && spt[1][i] != '\n')
		i++;
	spt[1][i] = '\0';
	im->ptr_image = mlx_xpm_file_to_image(cube->mlx, spt[1], \
	&im->width, &im->height);
	if (im->ptr_image == NULL)
		return (free_db_array(spt), free_all(cube), \
	error(XPM_FILE, CONT), 1);
	im->img = mlx_get_data_addr(im->ptr_image, \
	&im->bits, &im->size, &im->endian);
	if (im->img == NULL)
		return (free_db_array(spt), free_all(cube), \
	error(IMG_ADDR, CONT), 1);
	return (free_db_array(spt), 0);
}

static int	add_color(char **spt, t_cube *cube, t_color *col)
{
	int		i;
	int		count;
	char	**rgb;

	i = 1;
	count = 0;
	while (count < 3)
	{
		if (spt[i] == NULL)
			return (free_db_array(spt), free_all(cube), \
			error(W_RGB, CONT), 1);
		rgb = ft_split(spt[i], ',');
		if (rgb == NULL)
			return (free_db_array(spt), free_all(cube), \
			error(MALLOC, CONT), 1);
		if (rgb[0] == NULL)
			return (free_db_array(rgb), free_db_array(spt), free_all(cube), \
			error(W_RGB, CONT), 1);
		if (fill_rgb(&count, cube, col, rgb))
			return (free_db_array(spt), free_db_array(rgb), 1);
		free_db_array(rgb);
		i++;
	}
	return (free_db_array(spt), 0);
}

static int	fill_rgb(int *count, t_cube *cube, t_color *col, char **rgb)
{
	int	j;
	int	len;

	j = -1;
	while (rgb[++j])
	{
		len = -1;
		while (rgb[j][++len])
			if (rgb[j][len] != '\0' && rgb[j][len] != '\n' \
			&& (len > 3 || ft_isdigit(rgb[j][len]) == 0))
				return (free_all(cube), error(W_RGB, CONT), 1);
		if (*count == 0)
			col->red = ft_atoi(rgb[j]);
		else if (*count == 1)
			col->gre = ft_atoi(rgb[j]);
		else if (*count == 2)
			col->blu = ft_atoi(rgb[j]);
		if ((*count == 0 && (col->red < 0 || col->red > 255)) \
		|| (*count == 1 && (col->gre < 0 || col->gre > 255)) \
		|| (*count == 2 && (col->blu < 0 || col->blu > 255)))
			return (free_all(cube), error(W_RGB, CONT), 1);
		(*count)++;
	}
	return (0);
}
