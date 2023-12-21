/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encodage_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:02:37 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/21 18:49:14 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	**fill_texture_content(t_cube *cube, t_image texture);
static int	**fill_array(int **text_array, t_image texture);

void	encodage_texture(int fd, t_cube *cube)
{
	cube->no.pix_img = fill_texture_content(cube, cube->no);
	if (cube->no.pix_img == NULL)
		return (close(fd), error(MALLOC, END));
	cube->so.pix_img = fill_texture_content(cube, cube->so);
	if (cube->so.pix_img == NULL)
		return (close(fd), error(MALLOC, END));
	cube->we.pix_img = fill_texture_content(cube, cube->we);
	if (cube->we.pix_img == NULL)
		return (close(fd), error(MALLOC, END));
	cube->ea.pix_img = fill_texture_content(cube, cube->ea);
	if (cube->ea.pix_img == NULL)
		return (close(fd), error(MALLOC, END));
}

static int	**fill_texture_content(t_cube *cube, t_image texture)
{
	int	**array;
	int	y;

	array = malloc(sizeof(int *) * (texture.height));
	if (array == NULL)
		return (free_all(cube), NULL);
	y = -1;
	while (++y < texture.height)
	{
		array[y] = malloc(sizeof(int) * (texture.width));
		if (array[y] == NULL)
		{
			y = 0;
			while (array[y] != NULL)
				free(array[y++]);
			return (free_all(cube), free(array), NULL);
		}
	}
	return (fill_array(array, texture));
}

static int	**fill_array(int **array, t_image texture)
{
	int	y;
	int	x;

	y = 0;
	while (y < texture.height)
	{
		x = 0;
		while (x < texture.width)
		{
			array[y][x] = *(int *)(texture.img + \
				(y * texture.size + x * (texture.bits / 8)));
			x++;
		}
		y++;
	}
	return (array);
}
