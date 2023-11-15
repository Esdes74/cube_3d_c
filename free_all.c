/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:50:13 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/15 17:35:26 by eslamber         ###   ########.fr       */
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
	mlx_destroy_window(cube->mlx, cube->win);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	if (cube->map != NULL)
		free_db_array(cube->map);
}

static void	destroy_image(t_cube *cube, t_image *im)
{
	if (im->ptr_image != NULL)
		mlx_destroy_image(cube->mlx, im->ptr_image);
}
