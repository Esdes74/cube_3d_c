/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:00:59 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/22 19:36:55 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*pass_newline(const int fd, char *line)
{
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}
