/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:40:33 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/13 10:36:25 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	initialisation(t_cube *cube);

int	main(int ac, char **av)
{
	t_cube	cube;

	if (ac == 2)
	{
		initialisation(&cube);
		parsing(av[1], &cube);
	}
	return (0);
}

static void	initialisation(t_cube *cube)
{
	cube->f.first = 0;
	cube->c.first = 0;
	cube->f.second = 0;
	cube->c.second = 0;
	cube->f.third = 0;
	cube->c.third = 0;
	cube->no = NULL;
	cube->so = NULL;
	cube->we = NULL;
	cube->ea = NULL;
	cube->map = NULL;
}
