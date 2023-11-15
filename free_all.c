/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:50:13 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/15 15:25:33 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_all(t_cube *cube)
{
	mlx_destroy_window(cube->mlx, cube->win);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
}
