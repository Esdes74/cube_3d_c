/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:00:59 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/07 19:56:26 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>

char	*pass_newline(const int fd, char *line)
{
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

int	encodage_couleur(t_color col)
{
	int	res;

	res = 0;
	res = res | (col.red << 16);
	res = res | (col.gre << 8);
	res = res | col.blu;
	printf("H = %d, size = %d, res = %d\n", col.red, col.gre, col.blu);
	printf("H = %d\n", res);
	return (res);
}
