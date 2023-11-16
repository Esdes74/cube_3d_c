/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:40:33 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/16 10:36:36 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	init_cube(t_cube *cube);
static void	init_image(t_image *im);
static void	initialisation(t_cube *cube);

int	main(int ac, char **av)
{
	t_cube	cube;

	if (ac != 2)
		error(NBR_ARG, END);
	init_cube(&cube);
	initialisation(&cube);
	/* mlx_loop(cube.mlx); */
	parsing(av[1], &cube);
	ft_printf_fd(2, "test cube->no %p", cube.no.img);
	free_all(&cube);
	return (0);
}

static void	init_cube(t_cube *cube)
{
	cube->c.red = 0;
	cube->f.red = 0;
	cube->f.gre = 0;
	cube->c.gre = 0;
	cube->f.blu = 0;
	cube->c.blu = 0;
	init_image(&cube->no);
	init_image(&cube->so);
	init_image(&cube->we);
	init_image(&cube->ea);
	cube->mlx = NULL;
	cube->win = NULL;
	cube->map = NULL;
}

static void	init_image(t_image *im)
{
	im->img = NULL;
	im->ptr_image = NULL;
	im->bits = 0;
	im->size = 0;
	im->endian = 0;
	im->width = 0;
	im->height = 0;
}

static void	initialisation(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (cube->mlx == NULL)
		error(MLX, END);
	cube->win = mlx_new_window(cube->mlx, WIN_W, WIN_H, NAME);
	if (cube->win == NULL)
		return (mlx_destroy_display(cube->mlx), free(cube->mlx), \
	error(WIN, END));
}
