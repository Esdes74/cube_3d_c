/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_db_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estelamb <estelamb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:04:25 by eslamber          #+#    #+#             */
/*   Updated: 2023/12/21 09:52:15 by estelamb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_mem.h"

void	free_db_array(char **array)
{
	size_t	len;

	len = 0;
	while (array[len])
		free(array[len++]);
	free(array);
}
