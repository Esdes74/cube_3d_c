/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:50:13 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/21 18:49:26 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	destroy_image(t_cube *cube, t_image *im);

void	free_all(t_cube *cube)
{
	destroy_image(cube, &cube->no);
	destroy_image(cube, &cube->so);
	destroy_image(cube, &cube->ea);
	destroy_image(cube, &cube->we);
	destroy_image(cube, &cube->screen);
	mlx_destroy_window(cube->mlx, cube->win);
	mlx_destroy_display(cube->mlx);
	if (cube->map != NULL)
		free_db_array(cube->map);
	if (cube->no.pix_img != NULL)
		free_db_void_array((void **) cube->no.pix_img, cube->no.width);
	if (cube->so.pix_img != NULL)
		free_db_void_array((void **) cube->so.pix_img, cube->so.width);
	if (cube->we.pix_img != NULL)
		free_db_void_array((void **) cube->we.pix_img, cube->we.width);
	if (cube->ea.pix_img != NULL)
		free_db_void_array((void **) cube->ea.pix_img, cube->ea.width);
	free(cube->mlx);
}

static void	destroy_image(t_cube *cube, t_image *im)
{
	if (im->ptr_image != NULL)
		mlx_destroy_image(cube->mlx, im->ptr_image);
}
