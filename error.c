/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:40:33 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/15 12:57:48 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	error(t_error err)
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
	exit(1);
}
