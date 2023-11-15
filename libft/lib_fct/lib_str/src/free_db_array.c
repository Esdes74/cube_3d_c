/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_db_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eslamber <eslamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:04:25 by eslamber          #+#    #+#             */
/*   Updated: 2023/11/15 17:10:14 by eslamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_str.h"

void	free_db_array(char **array)
{
	size_t	len;

	len = 0;
	while (array[len])
		free(array[len++]);
	free(array);
}