/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_db_void_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estelamb <estelamb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:51:58 by estelamb          #+#    #+#             */
/*   Updated: 2023/12/21 09:59:13 by estelamb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_mem.h"

void	free_db_void_array(void **array, size_t x)
{
	size_t	len;

	len = 0;
	while (len < x)
		free(array[len++]);
	free(array);
}
