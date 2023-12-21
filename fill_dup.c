/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:53:55 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/21 18:49:21 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	fill_dup(const long long int i, const long long int j, char **dup)
{
	if (dup[i][j] == '0' || dup[i][j] == ' ')
	{
		if (dup[i + 1] != NULL && j < (long long int) ft_strlen(dup[i + 1]) && \
		(dup[i + 1][j] == 'X' || dup[i + 1][j] == 'I'))
			dup[i][j] = 'X';
		else if (i != 0 && j < (long long int) ft_strlen(dup[i - 1]) && \
		(dup[i - 1][j] == 'X' || dup[i - 1][j] == 'I'))
			dup[i][j] = 'X';
		else if (dup[i][j] != '\0' && \
		(dup[i][j + 1] == 'X' || dup[i][j + 1] == 'I'))
			dup[i][j] = 'X';
		else if (j > 0 && \
		(dup[i][j - 1] == 'X' || dup[i][j - 1] == 'I'))
			dup[i][j] = 'X';
	}
}
