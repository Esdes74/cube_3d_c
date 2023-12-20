/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estelamb <estelamb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:40:33 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/20 15:16:18 by estelamb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "display.h"

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
	parsing(av[1], &cube);
	raycasting(&cube);
	free_all(&cube);
	return (0);
}

static void	init_cube(t_cube *cube)
{
	cube->perso = 0;
	cube->size_map = 0;
	cube->personnage.x = 0;
	cube->personnage.y = 0;
	cube->personnage.orient = NONE;
	cube->c.red = -1;
	cube->f.red = -1;
	cube->f.gre = -1;
	cube->c.gre = -1;
	cube->f.blu = -1;
	cube->c.blu = -1;
	init_image(&cube->no);
	init_image(&cube->so);
	init_image(&cube->we);
	init_image(&cube->ea);
	cube->screen = NULL;
	cube->mlx = NULL;
	cube->win = NULL;
	cube->map = NULL;
}

static void	init_image(t_image *im)
{
	im->img = NULL;
	im->ptr_image = NULL;
	im->pix_img = NULL;
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
	cube->screen = mlx_new_image(cue->mlx, WIN_W, WIN_H);
	if (cube->screen == NULL)
		return (mlx_destroy_display(cube->mlx), free(cube->mlx), \
	error(SCREEN, END));
	cube->win = mlx_new_window(cube->mlx, WIN_W, WIN_H, NAME);
	if (cube->win == NULL)
		return (mlx_destroy_image(cube->mlx, cube->screen), \
	mlx_destroy_display(cube->mlx), free(cube->mlx), error(WIN, END));
}
