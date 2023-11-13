/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:40:33 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/13 10:36:25 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void verif_arg(char *av);

void    parsing(char *av, t_cube *cube)
{
    (void) cube;
    verif_arg(av);
}

static void verif_arg(char *av)
{
    int i;

    i = 0;
    while (av[i++])
        i++;
    if (av[i - 1] != 'b' || av[i - 2] != 'u' || av[i - 3] != 'c' || \
    av[i - 4] != '.')
        error(EXTENSION);
}
