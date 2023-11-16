/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:40:33 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/16 09:31:27 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	error(t_error err, t_mod mod)
{
	if (err == NBR_ARG)
		ft_printf("Error\nMust have 2 arguments\n");
	else if (err == EXTENSION)
		ft_printf("Error\nWrong extension try with \".cub\"\n");
	else if (err == OPEN)
		ft_printf("Error\nProblem with open function\n");
	else if (err == MLX)
		ft_printf("Error\nWrong initialisation of mlx\n");
	else if (err == WIN)
		ft_printf("Error\nWrong initialisation of window\n");
	else if (err == EMPTY_FILE)
		ft_printf("Error\nEmpty file\n");
	else if (err == UNCOMPLETE_FILE)
		ft_printf("Error\nUncomplete file\n");
	else if (err == MALLOC)
		ft_printf("Error\nProblem with malloc function\n");
	else if (err == TEXTURE_FORMAT)
		ft_printf("Error\nTexture not in a good format\n");
	else if (err == XPM_FILE)
		ft_printf("Error\nCan't open texture file\n");
	else if (err == IMG_ADDR)
		ft_printf("Error\nCan't find adress of image texture in memory\n");
	if (mod == END)
		exit(1);
}
