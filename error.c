/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:40:33 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/16 12:14:57 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	error_bis(t_error err);

void	error(t_error err, t_mod mod)
{
	if (err == NBR_ARG)
		ft_printf_fd(2, "Error\nMust have 2 arguments\n");
	else if (err == EXTENSION)
		ft_printf_fd(2, "Error\nWrong extension try with \".cub\"\n");
	else if (err == OPEN)
		ft_printf_fd(2, "Error\nProblem with open function\n");
	else if (err == MLX)
		ft_printf_fd(2, "Error\nWrong initialisation of mlx\n");
	else if (err == WIN)
		ft_printf_fd(2, "Error\nWrong initialisation of window\n");
	else if (err == EMPTY_FILE)
		ft_printf_fd(2, "Error\nEmpty file\n");
	else if (err == UNCOMPLETE_FILE)
		ft_printf_fd(2, "Error\nUncomplete file\n");
	else if (err == MALLOC)
		ft_printf_fd(2, "Error\nProblem with malloc function\n");
	else if (err == XPM_FILE)
		ft_printf_fd(2, "Error\nCan't open texture file\n");
	else if (err == IMG_ADDR)
		ft_printf_fd(2, \
	"Error\nCan't find adress of image texture in memory\n");
	else
		error_bis(err);
	if (mod == END)
		exit(1);
}

static void	error_bis(t_error err)
{
	if (err == TEXTURE_FORMAT)
		ft_printf_fd(2, "Error\nTexture not in good format\n");
	else if (err == WRONG_IDENTIFIER)
		ft_printf_fd(2, "Error\nWrong arguments in file\n");
	else if (err == WRONG_RGB)
		ft_printf_fd(2, "Error\nWrong RGB format\n");
}